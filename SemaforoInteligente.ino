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
#define trigger2    6
#define echo2       7

//Leds do semáforo
#define verde1      8
#define vermelho1   9
#define verde2      10
#define vermelho2   11

//Inciando sensores ultrassonicos
Ultrasonic ultrasonico1(trigger1, echo1);
Ultrasonic ultrasonico2(trigger2, echo2);

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
  pinMode(vermelho1, OUTPUT);
  pinMode(verde2, OUTPUT);
  pinMode(vermelho2, OUTPUT);

  //Iniciando um monitor serial para debugar os sensores
  Serial.begin(9600);
}

void loop() {
  //Estado inicial dos leds
  digitalWrite(verde1, HIGH);
  digitalWrite(vermelho1, LOW);
  digitalWrite(verde2, LOW);
  digitalWrite(vermelho2, HIGH);
  
  //Le as informacoes do sensor, em cm
  float dist2;
  long microsec = ultrasonico2.timing();
  dist2 = ultrasonico2.convert(microsec, Ultrasonic::CM);
  
   //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(dist2);
  delay(1000);

  //Leitura da distancia
  
  if(dist2 <= offset){
     delay(delayMin);
     digitalWrite(verde1, LOW);
     delay(delayMed);
     digitalWrite(vermelho1, HIGH);
     delay(delayMax);
     digitalWrite(verde2, HIGH);
     digitalWrite(vermelho2, LOW);
     delay(tempoPassagem);  
  }
  

}
