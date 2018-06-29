#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>


//Biblioteca do sensor Ultrassonico
#include <Ultrasonic.h>

//Pinos echo e trigger dos sensores ultrasssonicos
#define trigger1    4
#define echo1       5


//Leds do semáforo
#define verde1      8
#define amarelo1    9
#define vermelho1   10
#define verde2      11
#define amarelo2    12
#define vermelho2   13

//Inciando sensores ultrassonicos
Ultrasonic ultrasonico1(trigger1, echo1);


//Distânicia de offset
#define offset 10

//Padrões de delay

#define delayMin  500
#define delayMed  1000
#define delayMax  2000
#define tempoPassagem 8000

void setup() {
  //Configurando portas dos leds como saída
  pinMode(verde1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(vermelho1, OUTPUT);
  pinMode(verde2, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(vermelho2, OUTPUT);

  //Iniciando um monitor serial para debugar os sensores
  Serial.begin(9600);
}

void pisca(int x, int vezes) {
  int aux = 0;
  while(aux < vezes) {
    digitalWrite(x, LOW);
    delay(1000);
    digitalWrite(x, HIGH);
    delay(1000);
    aux = aux + 1;
  }
  digitalWrite(x, LOW);
}

void carro_vermelho() {
  pisca(verde1, 3);
  digitalWrite(amarelo1, HIGH);
  delay(2000);
  digitalWrite(amarelo1, LOW);
  digitalWrite(vermelho1, HIGH);
  delay(1000);
  digitalWrite(vermelho2, LOW);
  digitalWrite(verde2, HIGH);
}

void carro_verde() {
  pisca(verde2, 3);
  digitalWrite(amarelo2, HIGH);
  delay(2000);
  digitalWrite(amarelo2, LOW);
  digitalWrite(vermelho2, HIGH);
  delay(1000);
  digitalWrite(verde1, HIGH);
  digitalWrite(vermelho1, LOW);
}

void loop() {
  //Estado inicial dos leds
  digitalWrite(verde1, HIGH);
  digitalWrite(amarelo1, LOW);
  digitalWrite(vermelho1, LOW);
  digitalWrite(verde2, LOW);
  digitalWrite(amarelo2, LOW);
  digitalWrite(vermelho2, HIGH);
  
  //Le as informacoes do sensor, em cm
  float dist2;
  long microsec = ultrasonico1.timing();
  dist2 = ultrasonico1.convert(microsec, Ultrasonic::CM);
  
   //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(dist2);
  delay(1000);

  //Leitura da distancia
  
  if(dist2 <= offset){
    carro_vermelho();
    delay(5000);
    carro_verde();
    delay(9000);
  }
}
