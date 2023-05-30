#include <LiquidCrystal_I2C.h>
#define TRIG 9
#define ECHO 10
#define bomba 8

const float VELOCIDAD = 0.0343;
float TIME;
float DISTANCIA;
LiquidCrystal_I2C pantalla(0x27, 16, 2);
int pinBuzzer = 4;

// Definir la melodía de la canción
int melodia[] = {262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 392, 440, 392, 349, 330, 262, 262, 392, 330, 262, 262, 392, 330, 262, 294, 262};

// Duración de cada nota en milisegundos
int duracionNotas[] = {200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 200, 200, 200, 200, 400, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400};

int indiceMelodia = 0;

void setup() {
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(bomba, OUTPUT);
  pantalla.init();
  pantalla.backlight();
  pantalla.clear();
  attachInterrupt(digitalPinToInterrupt(2), llenar, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), pausa, HIGH);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  TIME = pulseIn(ECHO, HIGH);
  DISTANCIA = (TIME) * VELOCIDAD / 2;
  Serial.println(DISTANCIA);
  delay(200);
  if (DISTANCIA >= 13) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:15%");
  }
  if (DISTANCIA >= 12 && DISTANCIA < 13) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:29%");
  }
  if (DISTANCIA >= 11 && DISTANCIA < 12) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:43%");
  }
  if (DISTANCIA >= 10 && DISTANCIA < 11) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:57%");
  }
  if (DISTANCIA >= 9 && DISTANCIA < 10) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:71%");
  }
  if (DISTANCIA >= 8 && DISTANCIA < 9) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:85%");
  }
  if (DISTANCIA >= 7 && DISTANCIA < 8) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:92%");
  }
  if (DISTANCIA >= 6 && DISTANCIA < 7) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Cantidad:100%");

  }

  // Reproducir melodía si se cumple la distancia
  if (DISTANCIA <= 13 && DISTANCIA >= 6) {
    // Reproducir nota en el buzzer
    tone(pinBuzzer, melodia[indiceMelodia], duracionNotas[indiceMelodia]);

    // Incrementar el índice de la melodía
    indiceMelodia = (indiceMelodia + 1) % sizeof(melodia);
  } else {
    // Si no se cumple la distancia, detener la reproducción
    noTone(pinBuzzer);
  }
}

void llenar() {
  digitalWrite(bomba, LOW);
  tone(pinBuzzer, 200);
}

void pausa() {
  digitalWrite(bomba, HIGH);
  noTone(pinBuzzer);
}
