/*------------------------------------------------------------------*/
/*-------------------------< IoT ESP 32 >---------------------------*/
/*--------------------< Controle de Hortas >------------------------*/
/*-----------------------< Versão 1.0.0 >---------------------------*/
/*----------------< Criado por Carlos Cordeiro >--------------------*/
/*------------------------< 06/02/2021 >----------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

// Bibliotecas utiliadas no projeto
#include <WiFi.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DEBUG true

// Parâmetros de Rede WiFi
const char* ssid = "SUA_SS_ID";
const char* password = "SENHA";

// Criando um LCD de 16x2 no endereço 0x20
LiquidCrystal_I2C lcd(0x27,16,2);

// Configurção dos Pinos
#define DHTPIN 5                // Pino do sensor de umidade e temperatura
#define LDRPIN 36               // Pino do sensor de luz
#define VASO_1_PIN 13           // Pino do vaso número 1
#define VASO_2_PIN 12           // Pino do vaso número 2
#define VASO_3_PIN 14           // Pino do vaso número 3
#define VASO_4_PIN 27           // Pino do vaso número 4
#define VASO_5_PIN 26           // Pino do vaso número 5
#define VASO_6_PIN 25           // Pino do vaso número 6
#define VASO_7_PIN 33           // Pino do vaso número 7
#define VASO_8_PIN 19           // Pino do vaso número 8
#define VASO_9_PIN 21           // Pino do vaso número 9
#define VASO_10_PIN 22          // Pino do vaso número 10

//Definindo as saídas difitais para as bombas de irrigação automática

#define BIA1                    // Pino da Bomba de Irrigação do Vaso 1
#define BIA2                    // Pino da Bomba de Irrigação do Vaso 2
#define BIA3                    // Pino da Bomba de Irrigação do Vaso 3
#define BIA4                    // Pino da Bomba de Irrigação do Vaso 4
#define BIA5                    // Pino da Bomba de Irrigação do Vaso 5
#define BIA6                    // Pino da Bomba de Irrigação do Vaso 6
#define BIA7                    // Pino da Bomba de Irrigação do Vaso 7
#define BIA8                    // Pino da Bomba de Irrigação do Vaso 8
#define BIA9                    // Pino da Bomba de Irrigação do Vaso 9
#define BIA10                   // Pino da Bomba de Irrigação do Vaso 10

//Definindo os níveis de água para cada tipo de planta



// Definição do Sensor DHT11
#define DHTTYPE DHT11

// Inicialização do sensor DHT
DHT dht(DHTPIN, DHTTYPE, 15);

// Definição do Host
const char* host = "dweet.io";
const char* thing = "Nome_do_Dispositivo_no_Dweet";  // Nome do dispositivo IoT na Rede Dweet.io

void setup() {

  // Iniciar comunicação serial
  Serial.begin(115200);
  delay(1000);

  // Definir os modos de entrada analógica dos sensores na placa ESP32

  pinMode (LDRPIN, INPUT);
  pinMode (VASO_1_PIN, INPUT);
  pinMode (VASO_2_PIN, INPUT);
  pinMode (VASO_3_PIN, INPUT);
  pinMode (VASO_4_PIN, INPUT);
  pinMode (VASO_5_PIN, INPUT);
  pinMode (VASO_6_PIN, INPUT);
  pinMode (VASO_7_PIN, INPUT);
  pinMode (VASO_8_PIN, INPUT);
  pinMode (VASO_9_PIN, INPUT);
  pinMode (VASO_10_PIN, INPUT);

  // Definir os modos de saída digital dos acionamentos na placa ESP32

  pinMode (BIA1, OUTPUT);
  pinMode (BIA2, OUTPUT);
  pinMode (BIA3, OUTPUT);
  pinMode (BIA4, OUTPUT);
  pinMode (BIA5, OUTPUT);
  pinMode (BIA6, OUTPUT);
  pinMode (BIA7, OUTPUT);
  pinMode (BIA8, OUTPUT);
  pinMode (BIA9, OUTPUT);
  pinMode (BIA10, OUTPUT);
        
  // Inicializar o sensor DHT
  dht.begin();

  // Conectando com a Rede WiFi
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  Serial.print("Connecting to ");
  Serial.println(host);

  // Usando WiFiClient para criar uma conexão TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Lendo umidade
  int h = dht.readHumidity();

  // Lendo temperatura em celcius
  int t = dht.readTemperature();

  // Lendo luminosidade no LDR e convertendo para porcentagem de luz
  int LDR = map((float(analogRead(LDRPIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 1 e convertendo em percentual de umidade
  int UV1 = map((float(analogRead(VASO_1_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 2 e convertendo em percentual de umidade
  int UV2 = map((float(analogRead(VASO_2_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 3 e convertendo em percentual de umidade
  int UV3 = map((float(analogRead(VASO_3_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 4 e convertendo em percentual de umidade
  int UV4 = map((float(analogRead(VASO_4_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 5 e convertendo em percentual de umidade
  int UV5 = map((float(analogRead(VASO_5_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 6 e convertendo em percentual de umidade
  int UV6 = map((float(analogRead(VASO_6_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 7 e convertendo em percentual de umidade
  int UV7 = map((float(analogRead(VASO_7_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 8 e convertendo em percentual de umidade
  int UV8 = map((float(analogRead(VASO_8_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 9 e convertendo em percentual de umidade
  int UV9 = map((float(analogRead(VASO_9_PIN))), 0, 4095, 100, 0);

  // Lendo as informações do vaso 10 e convertendo em percentual de umidade
  int UV10 = map((float(analogRead(VASO_10_PIN))), 0, 4095, 100, 0);

  delay(1000);

  // Enviandp requisição para o servidor
  client.print(String("GET /dweet/for/Nome_do_Dispositivo_no_Dweet?Temperatura=") + String(t) +          // Envia a informação da temperatura do ar
               "&Umidade=" + String(h) +                                                        // Envia a informação da umidade relativa do ar
               "&Luminosidade=" + String(LDR) +                                                 // Envia a informação da quantidade de luz presente no local do sensor de luz LDR
               "&Umidade Vaso 1=" + String(UV1) +                                               // Envia a informação da umidade do vaso 1, em %
               "&Umidade Vaso 2=" + String(UV2) +                                               // Envia a informação da umidade do vaso 2, em %
               "&Umidade Vaso 3=" + String(UV3) +                                               // Envia a informação da umidade do vaso 3, em %
               "&Umidade Vaso 4=" + String(UV4) +                                               // Envia a informação da umidade do vaso 4, em %
               "&Umidade Vaso 5=" + String(UV5) +                                               // Envia a informação da umidade do vaso 5, em %
               "&Umidade Vaso 6=" + String(UV6) +                                               // Envia a informação da umidade do vaso 6, em %
               "&Umidade Vaso 7=" + String(UV7) +                                               // Envia a informação da umidade do vaso 6, em %
               "&Umidade Vaso 8=" + String(UV8) +                                               // Envia a informação da umidade do vaso 6, em %
               "&Umidade Vaso 9=" + String(UV9) +                                               // Envia a informação da umidade do vaso 6, em %
               "&Umidade Vaso 10=" + String(UV10) + " HTTP/1.1\r\n" +                             // Envia a informação da umidade do vaso 10, em %
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(1000);

  // Lendo as linhas e imprimindo na tela
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }


  //Imprime na tela os valores dos parâmetros medidos

  Serial.println();
  Serial.println("Temperatura: ");
  Serial.print(t);
  
  Serial.println("Umidade: ");
  Serial.print(h);
  
  Serial.println("Luz: ");
  Serial.print(LDR);
  
  Serial.println("Umidade do Solo - Vaso 1: ");
  Serial.print(UV1);
  
  Serial.println("Umidade do Solo - Vaso 2: ");
  Serial.print(UV2);
  
  Serial.println("Umidade do Solo - Vaso 3: ");
  Serial.print(UV3);
  
  Serial.println("Umidade do Solo - Vaso 4: ");
  Serial.print(UV4);
  
  Serial.println("Umidade do Solo - Vaso 5: ");
  Serial.print(UV5);
  
  Serial.println("Umidade do Solo - Vaso 6: ");
  Serial.print(UV6);
  
  Serial.println("Umidade do Solo - Vaso 7: ");
  Serial.print(UV7);

  Serial.println("Umidade do Solo - Vaso 8: ");
  Serial.print(UV8);

  Serial.println("Umidade do Solo - Vaso 9: ");
  Serial.print(UV9);

  Serial.println("Umidade do Solo - Vaso 10: ");
  Serial.print(UV10);

  lcd.init ();
  lcd.backlight();
  lcd.clear ();     
  lcd.print("Umidade: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Temp.: ");
  lcd.print(t);
  lcd.print(" C");
 
  
  Serial.println("closing connection");

  // Repeat
  delay(10);
}
