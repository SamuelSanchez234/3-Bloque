#include <Stepper.h>
#define Trig 4
#define echo 5

int piso_1 = 0;
int piso_2 = 0;
const int rotacionc = 2048;

const float velocidad = 0.0343;
float time;
float distancia;

Stepper myStepper = Stepper(rotacionc, 8, 10, 9, 11);

void setup() {
  pinMode(Trig,OUTPUT);
  pinMode(echo,INPUT);
  myStepper.setSpeed(10);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),piso1,HIGH);
  attachInterrupt(digitalPinToInterrupt(3),piso2,CHANGE);
}

void loop() {
medida();
Serial.println(distancia);


Serial.println("todotranqui");
//distancia = 2
//distancia = 15

if(piso_1 == 1){
myStepper.step(2048);
piso_1 = piso_1-piso_1;
}

if(piso_2 == 1){
myStepper.step(-2048);
piso_2 = piso_2-piso_2;
}

}

void piso1(){
piso_1 = 1;
Serial.println("interrupcionabajo");
}

void piso2(){
piso_2 = 1;
Serial.println("interrupcionarriba");
}

void medida(){
digitalWrite(Trig, HIGH);
delay(1);
digitalWrite(Trig, LOW);
time = pulseIn(echo, HIGH);
distancia = (time)*velocidad/2;
}