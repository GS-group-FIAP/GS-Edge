💧 Projeto: Monitoramento de Umidade e Nível da Água

🎯 Descrição
Este projeto consiste em um sistema automatizado para monitoramento de umidade relativa do ar e nível de água, ideal para aplicação em áreas de risco de enchentes ou estiagens.
Utilizando sensores DHT22 e ultrassônico, o sistema detecta valores fora do ideal, informa a situação em tempo real por um display LCD 16x2 e emite alertas visuais (LEDs) e sonoros (buzzer). Além disso, registra médias periódicas na memória EEPROM do Arduino e utiliza um módulo RTC DS1307 para manter registros com data e hora precisas.

⚙️ Componentes Utilizados
Componente
Função
Arduino Uno
Microcontrolador principal
Sensor DHT22
Mede temperatura e umidade do ar
Sensor Ultrassônico HC-SR04
Mede a distância do nível da água
RTC DS1307 (com I2C)
Relógio de tempo real
Display LCD 16x2 com I2C
Exibe as leituras e status do sistema
EEPROM (interna do Arduino)
Armazena médias de umidade e altura
Buzzer
Emite alertas sonoros em situações críticas
LEDs (Verde, Amarelo, Vermelho)
Indicadores visuais de situação
Protoboard + jumpers
Conexões físicas


🖼️ Diagrama de Montagem
Conexões importantes:
DHT22: Pino digital 2


Sensor Ultrassônico:


Trigger: Pino 8


Echo: Pino 9


LCD I2C: SDA (A4), SCL (A5)


LEDs: Verde (pino 4), Amarelo (pino 5), Vermelho (pino 6)


Buzzer: Pino 7



💡 Funcionalidades
✅ Monitoramento Ambiental
Umidade relativa do ar com DHT22.


Altura da água com sensor ultrassônico.


Leituras em tempo real no LCD e monitor serial.


✅ Indicadores Visuais e Sonoros
LED Verde: Condições ideais.


LED Amarelo: Situação de atenção.


LED Vermelho + Buzzer: Situação crítica (risco de seca/enchente).


✅ Armazenamento de Dados
EEPROM salva médias de umidade e altura a cada 60 segundos, mesmo após desligar.


✅ Exibição no LCD
Exibe:


Data e hora atual.


Leituras atuais.


Mensagens como "TUDO OK", "UMIDADE BAIXA", "NÍVEL ALTO", etc.



📊 Faixas de Referência
Parâmetro
Ideal
Alerta (Amarelo)
Crítico (Vermelho + Buzzer)
Umidade
30% - 80%
Fora da faixa
<40% (seca) ou >65% (excesso)
Altura da água
80cm - 200cm
Fora da faixa
<77cm ou >203cm


📝 Pontos Interessantes
Armazena médias na EEPROM a cada minuto.


Usa módulo RTC para manter registros temporais.


Controla LEDs e buzzer com base nas faixas medidas.


Códigos organizados com funções para leitura, exibição e controle.


Projeto facilmente adaptável para fins reais (chuvas, poços, cisternas etc).



✅ Possíveis Melhorias Futuras
📶 Adição de módulo WiFi (ESP8266/ESP32) para monitoramento remoto.


💾 Log histórico em cartão SD.


📈 Visualização dos dados em gráficos via plataforma web.


🔧 Interface de ajuste dinâmico das faixas ideais.



💻 Bibliotecas Utilizadas
Wire.h → Comunicação I2C


RTClib.h → Controle do módulo RTC


LiquidCrystal_I2C.h → Controle do display LCD


DHT.h → Controle do sensor DHT22


EEPROM.h → Armazenamento persistente de dados



🚧 Como Montar
Monte o circuito conforme o esquema acima.


Carregue o código na IDE Arduino.


Abra o monitor serial (9600 baud).


Observe os dados em tempo real no LCD e serial.


Verifique os LEDs e o buzzer conforme os valores medidos.



🖥️ Como Rodar este Projeto
✅ Simulação Online com Wokwi
Este projeto pode ser testado totalmente online via Wokwi, permitindo ajustes e testes sem componentes físicos.
➡️ Clique aqui para simular no Wokwi
🚀 Passos para simulação
Acesse o link acima.


Pressione “Start Simulation”.


Ajuste os valores do DHT22 e do sensor ultrassônico pelo painel lateral.


Observe:


O comportamento dos LEDs.


As mensagens no display.


O acionamento do buzzer.


Os dados armazenados periodicamente na EEPROM.



👨‍💻 Créditos
Desenvolvido por:
Kauê de Almeida Pena – RA: 564211


Gabriel Ferreira Machado – RA: 562330

Link Simulação: https://wokwi.com/projects/432655217224597505

