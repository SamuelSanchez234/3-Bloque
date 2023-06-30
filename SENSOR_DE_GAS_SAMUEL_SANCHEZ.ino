#include <LedControl.h> // Libreria de la Matriz Led

const int pinSensorGas = A0;      // Pin del sensor de gas
int inputgas = 2;
const int pinBuzzer = 3;         // Pin del buzzer
const int pinMatrixData = 13;     // Pin de datos de la matriz LED
const int pinMatrixClock = 11;    // Pin de reloj de la matriz LED
const int pinMatrixCs = 10;       // Pin de selección de la matriz LED

LedControl matrix = LedControl(pinMatrixData, pinMatrixClock, pinMatrixCs, 1);
volatile bool isAlertActive = false;

void setup() {
  pinMode(pinBuzzer, OUTPUT);
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);
  
  // Configurar interrupción por software
  attachInterrupt(digitalPinToInterrupt(pinSensorGas), gasInterrupt, CHANGE);
}

void loop() {
  // Realiza aquí otras tareas que desees mientras el sistema esté en funcionamiento
}

void gasInterrupt() {
  if (digitalRead(pinSensorGas) == HIGH) {
    // Sensor detectó humo o gas
    if (!isAlertActive) {
      isAlertActive = true;
      digitalWrite(pinBuzzer, HIGH);
      displayAlertAnimation();
      delay(1000);
    }
  } else {
    // Sensor volvió a su estado normal
    isAlertActive = false;
    digitalWrite(pinBuzzer, LOW);
    matrix.clearDisplay(0);
  }
}

void displayAlertAnimation() {
  // Define el patrón de peligro en la matriz LED
  byte dangerPattern[8] = {
    B00000000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00011000,
    B00000000
  };
  
  // Muestra el patrón en la matriz LED
  for (int i = 0; i < 8; i++) {
    matrix.setColumn(0, i, dangerPattern[i]);
  }
}
