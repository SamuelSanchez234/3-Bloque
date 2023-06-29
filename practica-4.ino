#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedControl.h"     // incluye libreria LedControl

LedControl lc=LedControl(11,13,10,1);
SoftwareSerial BT(8, 9);

char val;
int ledrojo = 7;
int ledrojo2 = 3;
int ledrojo3 = 6;
int ledrojo4 = 5;
const int servoPin1 = 4;

byte uno[8]= {        // array que contiene todos los elementos de las
  B00010000,        // filas necesarias por mostrar el digito uno
  B00110000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B00111000
};

Servo servo;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(ledrojo, OUTPUT);
  pinMode(ledrojo2, OUTPUT);
  servo.attach(servoPin1);
  lc.shutdown(0,false);     // enciende la matriz
  lc.setIntensity(0,4);     // establece brillo
  lc.clearDisplay(0);     // blanquea matriz
}



void loop() {

movimiento();

  if(BT.available() > 0){
    val = BT.read();
    Serial.println(val);
  }

  if(val == 'A'){
    digitalWrite(ledrojo, HIGH);
  }

  if(val == 'B'){
    digitalWrite(ledrojo, LOW);
  }

  if(val == 'C'){
    digitalWrite(ledrojo2, HIGH);
  }

  if(val == 'D'){
    digitalWrite(ledrojo2, LOW);
  }

    if(val == 'E'){
    digitalWrite(ledrojo3, HIGH);
  }

  if(val == 'F'){
    digitalWrite(ledrojo3, LOW);
  }

    if(val == 'G'){
    digitalWrite(ledrojo4, HIGH);
  }

  if(val == 'H'){
    digitalWrite(ledrojo4, LOW);
  }
  
  if(val == 'H'){
    digitalWrite(ledrojo4, LOW);
  }
  
  if(val == 'I'){
    mostrar_1();
  }
}

void movimiento(){
  while(BT.available() > 0){
    val = BT.read();
    Serial.println(val);
    servo.write(val);
    delay(10);
  }
}

void mostrar_1(){     // funcion mostrar_1
  for (int i = 0; i < 8; i++)     // bucle itera 8 veces por el array
  {
  lc.setRow(0,i,uno[i]);    // establece fila con valor de array uno en misma posicion
  }
}
