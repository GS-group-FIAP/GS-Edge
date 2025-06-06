#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <EEPROM.h>

#define LOG_OPTION 1
#define SERIAL_OPTION 0
#define UTC_OFFSET -3

#define PIN_TRIG 5
#define PIN_ECHO 4
#define DHTPIN 6
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;

const int BUZZER = 7;
const int LED_VERMELHO = 10;
const int LED_AMARELO = 9;
const int LED_VERDE = 8;

float umimedia = 0;
float altmedia = 0;
int settime = 0;
int umidMin = 0, umidMax = 0 ,altMin = 0, altMax = 0;
float alt = 0;  // Valor da altura medida 

// Controle de alarme
unsigned long tempoAlarme = 0;
bool buzzerTocando = false;
bool jaSoouNaZonaVermelha = false;

void setup() {
  lcd.begin(16, 2);

  dht.begin();
  rtc.begin();
  Serial.begin(9600);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  float umidSalva, altSalva;
  EEPROM.get(0, umidSalva);                   // Leitura da umidade média salva
  EEPROM.get(sizeof(float), altSalva);        // Leitura da altura média salva

  Serial.println("Médias salvas na EEPROM:");
  Serial.print("Umidade: "); Serial.print(umidSalva, 1); Serial.println(" %");
  Serial.print("Altura: "); Serial.print(altSalva, 1); Serial.println(" cm");
}

void loop() {
  checarUmidTemp(); // Define limites seguros

  // Medição da altura com sensor ultrassônico
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  int duration = pulseIn(PIN_ECHO, HIGH);
  alt = duration / 58.0; // Conversão para cm
  Serial.print("Distância em CM: ");

  float umid = dht.readHumidity(); // Lê umidade
  DateTime now = rtc.now();       // Horário atual

  // Exibe data e umidade no serial
  Serial.print("[");
  Serial.print(now.day()); Serial.print("/");
  Serial.print(now.month()); Serial.print("/");
  Serial.print(now.year()); Serial.print(" ");
  Serial.print(now.hour()); Serial.print(":");
  Serial.print(now.minute()); Serial.print(":");
  Serial.print(now.second()); Serial.print("] ");
  Serial.print(" | Umid: "); Serial.print(umid); Serial.print(" %");
  Serial.print(" | Alt: "); Serial.print(alt); Serial.println(" cm");
  

  // Verifica se valores estão dentro dos limites
  bool umidOK = (umid >= umidMin && umid <= umidMax);
  bool altOK = (alt >= altMin && alt <= altMax);

  lcd.clear();

  if (umidOK && altOK) {
    // Situação segura
    lcd.setCursor(4, 0);
    lcd.print("SEM RISCO");
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);
    jaSoouNaZonaVermelha = false;
  } else {
    // Situação de risco
    lcd.setCursor(3, 0);
    if (!umidOK)
      lcd.print(umid < umidMin ? "Pouca umidade" : "Alto Risco de");
    else if (!altOK)
      lcd.print(alt < altMin ? "Nivel Baixo" : "Nivel Alto");

    lcd.setCursor(3, 1);
    if (!umidOK)
      lcd.print(umid < umidMin ? "no ar" : "chuvas fortes");
    else if (!altOK)
      lcd.print(alt < altMin ? "de agua" : "de agua");

    digitalWrite(LED_VERDE, LOW);

    if (!altOK && (alt < altMin - 3 || alt > altMax + 3)) {
      // Alarme para situações críticas de umidade
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_AMARELO, LOW);
      if (!jaSoouNaZonaVermelha) {
        tone(BUZZER, 1000);
        jaSoouNaZonaVermelha = true;
      }
    } else {
      // Situação de alerta moderado
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      noTone(BUZZER);
      jaSoouNaZonaVermelha = false;
    }
  }

  // Acumula valores para média
  altmedia += alt;
  umimedia += umid;
  settime += 1;

  delay(1000); // Aguarda 1 segundo

  if (settime == 60) {
    // A cada 60 segundos, calcula médias e salva na EEPROM
    umimedia /= 60;
    altmedia /= 60;

    Serial.println("\nMédias (últimos 1 min):");
    Serial.print("Umidade: "); Serial.print(umimedia, 1); Serial.println(" %");
    Serial.print("Altura: "); Serial.print(altmedia, 1); Serial.println(" cm");

    EEPROM.put(0, umimedia);                     // Salva a umidade média
    EEPROM.put(sizeof(float), altmedia);         // Salva a altura média

    // Reinicia acumuladores
    altmedia = 0;
    umimedia = 0;
    settime = 0;
  }
}

// Define os limites de segurança para umidade e altura
void checarUmidTemp() {
  umidMin = 50;
  umidMax = 80;
  altMin = 80;
  altMax = 200;
  delay(300); // Pequeno atraso
}
