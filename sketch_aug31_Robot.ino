/*------------------------------------------------------------------*/
/*-----------------------< Robo Autônomo >--------------------------*/
/*-----------------------< Versão 1.0.0 >---------------------------*/
/*----------------< Criado por Carlos Cordeiro >--------------------*/
/*------------------------< 01/09/2020 >----------------------------*/
/*------------------------------------------------------------------*/
/*----------------< carlosccordeiro@uol.com.br >--------------------*/
/*------------------------------------------------------------------*/

#include <Ultrasonic.h>
#include <Wire.h> 
#include <Servo.h>

//Define os pinos para o trigger e echo do sensor ultrasonico A

#define pino_triggerA 12
#define pino_echoA 13

//Define os pinos para o trigger e echo do sensor ultrasonico A

#define pino_triggerB 10
#define pino_echoB 11

//Definie a variável que armazenará a distância medida pelo sensor ultrasônico

long dista;

//Definicoes dos módulos ultrassônicos

Ultrasonic ultrasonicA(pino_triggerA, pino_echoA);
Ultrasonic ultrasonicB(pino_triggerB, pino_echoB);

//Definicoes dos servo motores, caso sejam utilizados

Servo servomotorA;
Servo servomotorB;

//Definicoes pinos Arduino ligados ao módulo de Joystick

int pino_x = A4; //Pino ligado ao X do joystick
int pino_y = A5; //Pino ligado ao Y do joystick
int val_x;   //Armazena o valor do eixo X
int val_y;   //Armazena o valor do eixo Y

//Definicoes pinos Arduino ligados a entrada da Ponte H

// Motor A

    int IN1 = 2;
    int IN2 = 3;

// Velocidade do Motor A em modo PWM

    int VMA = 9;

// Motor B

    int IN3 = 4;
    int IN4 = 5;

// Velocidade do Motor B em modo PWM

    int VMB = 10;

// Definição dos parâmetrode c configuração

void setup()
{
  Serial.begin (9600);
  //Pinos de saída do motor A
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(VMA, OUTPUT);

  //Pinos de saída do motor B
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(VMB, OUTPUT);
}

// Funções de controle do robo

void calcular()
{

lerDistancia();

if (dista > 10){

moveFrente();
analogWrite (VMA,125);
analogWrite (VMA,125);
}

else // Para fins de teste, fazer o motor girar sempre à direita. Futuramente ele deve calcular o melhor caminho.

{
 
travarPosicao();

delay(1000);

analogWrite (VMA,100);
analogWrite (VMA,100);
movePraTras();

delay (1000);
analogWrite (VMA,50);
analogWrite (VMA,50);
girarDireita();

delay (1000);
calcular();

}

}
// Mover o robo para frente

void moveFrente()

{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void movePraTras()

{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarDireita()

{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarEsquerda()

{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void travarPosicao()

{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void lerDistancia ()

{
  float cmMsec;
  long microsec = ultrasonicA.timing();
  dista = ultrasonicA.convert(microsec, Ultrasonic::CM);
  return dista;
  }

void loop()
{

calcular();

// Caso seja aplicado o controle do robô com joystic, o código abaixo deverá ser utilizado.

//Recebe o valor do joystick, eixo X
  val_x = analogRead(pino_x);
  //Converte o valor lido para um valor entre -1 e 1 graus
  val_x = map(val_x, 0, 1023, -1, 1);
  


    //Recebe o valor do joystick, eixo X
  val_y = analogRead(pino_y);
  //Converte o valor lido para um valor entre -1 e 1 graus
  val_y = map(val_y, 0, 1023, -1, 1);

// Se a leitura do joystick for maior que zero, o robo se move para frente!
if (val_x >0 && val_y ==0)
{
moveFrente();

// Define a velocidade do motor em função do valor lido no joystick

VMA = val_x*255;
VMB = val_x*255;

}

// Se a leitura do joystick for menor que zero, o robo se move para trás!
else if (val_x <0 && val_y ==0)
{
movePraTras();

// Define a velocidade do motor em função do valor lido no joystick, convertendo o valor negativo em positivo!

VMA = val_x*255*-1;
VMB = val_x*255*-1;
}

// Se a leitura do joystick for igual a zero, o robo trava as rodas!
else if (val_x = 0 && val_y == 0)
{
travarPosicao();

// Define a velocidade do motor em função do valor lido no joystick

VMA = 0;
VMB = 0;
}

}

/*------------------------------------------------------------------*/
/*------------------------- Fim do Código --------------------------*/
/*------------------------------------------------------------------*/
