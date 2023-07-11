#include <SPI.h>			// incluye libreria bus SPI
#include <MFRC522.h>			// incluye libreria especifica para MFRC522
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int rojo = 2;
int verde = 3;
const int servoPin1 = 7;
int buzzer = 6;
Servo servo;
#define RST_PIN  9			// constante para referenciar pin de reset
#define SS_PIN  10			// constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN);	// crea objeto mfrc522 enviando pines de slave select y reset
LiquidCrystal_I2C lcd(0x27, 16, 2);// Inicializa el objeto LiquidCrystal_I2C para la pantalla LCD

byte LecturaUID[4]; 				// crea array para almacenar el UID leido
byte Usuario1[4]= {0xB2, 0x54, 0x9E, 0x1C} ;    // UID de tarjeta leido en programa 1
byte Usuario2[4]= {0x93, 0x4C,  0xED, 0x1B} ;    // UID de llavero leido en programa 1

void setup() {
  Serial.begin(9600);			// inicializa comunicacion por monitor serie a 9600 bps
  pinMode(buzzer,OUTPUT);
  SPI.begin();				// inicializa bus SPI
  mfrc522.PCD_Init();			// inicializa modulo lector
  Serial.println("Listo");		// Muestra texto Listo
  servo.attach(servoPin1);
  servo.write(0);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);

   Wire.begin();// Inicializa la comunicación I2C
  lcd.backlight();// Encender la retroiluminación de la LCD

  lcd.begin(16, 2);
  lcd.print("Ingresar tarjeta");//Imprime el texto en la LCD

}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())		// si no hay una tarjeta presente
    return;						// retorna al loop esperando por una tarjeta
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 		// si no puede obtener datos de la tarjeta
    return;						// retorna al loop esperando por otra tarjeta
    
    Serial.print("UID:");				// muestra texto UID:
    for (byte i = 0; i < mfrc522.uid.size; i++) {	// bucle recorre de a un byte por vez el UID
      if (mfrc522.uid.uidByte[i] < 0x10){		// si el byte leido es menor a 0x10
        Serial.print(" 0");				// imprime espacio en blanco y numero cero
        }
        else{						// sino
          Serial.print(" ");				// imprime un espacio en blanco
          }
          Serial.print(mfrc522.uid.uidByte[i], HEX);   	// imprime el byte del UID leido en hexadecimal
          LecturaUID[i]=mfrc522.uid.uidByte[i];   	// almacena en array el byte del UID leido      
          }
          
          Serial.print("\t");   			// imprime un espacio de tabulacion             
                    
          if(comparaUID(LecturaUID, Usuario1)){//llama a funcion comparaUID con Usuario1
            lcd.clear();
            Serial.println("Bienvenido");	// si retorna verdadero muestra texto bienvenida
            servo.write(90);
            delay(20);
            lcd.print("Jorge Sanchez");
            digitalWrite(verde, HIGH);
            digitalWrite(rojo, LOW);
            delay(2000);
            digitalWrite(verde, LOW);
            digitalWrite(rojo, HIGH);
            delay(2000);
            digitalWrite(rojo,LOW);
            delay(2000);
            lcd.clear();
            lcd.print("Ingresar tarjeta");//Imprime el texto en la LCD
            servo.write(90);
            tone(buzzer, 500,900);
            digitalWrite(buzzer,LOW);
            delay(100);

          }
          else if(comparaUID(LecturaUID, Usuario2)){// llama a funcion comparaUID con Usuario2
            lcd.clear();
            Serial.println("Bienvenido ");	// si retorna verdadero muestra texto bienvenida
            servo.write(90);
            delay(20);
            lcd.print("Samuel Sanchez");
            digitalWrite(verde, HIGH);
            digitalWrite(rojo, LOW);
            delay(2000);
            digitalWrite(verde, LOW);
            digitalWrite(rojo, HIGH);
            delay(2000);
            digitalWrite(rojo,LOW);
            delay(2000);
            lcd.clear();
            lcd.print("Ingresar tarjeta");//Imprime el texto en la LCD
            servo.write(0);
            tone(buzzer, 500,900);
            delay(1000);
          }	 
          else{						// si retorna falso
            Serial.println("Quien eres?");	// muestra texto equivalente a acceso denegado          
            lcd.clear(); 
            servo.write(0);
            lcd.print("Te conozco?");
            digitalWrite(rojo, HIGH);   
            delay(3000);
            

            lcd.clear();
            lcd.print("Ingresar tarjeta ");//Imprime el texto en la LCD
          }
                  mfrc522.PICC_HaltA();  		// detiene comunicacion con tarjeta                
}

boolean comparaUID(byte lectura[],byte usuario[])	// funcion comparaUID
{
  for (byte i=0; i < mfrc522.uid.size; i++){		// bucle recorre de a un byte por vez el UID
  if(lectura[i] != usuario[i])				// si byte de UID leido es distinto a usuario
    return(false);					// retorna falso
  }
  return(true);						// si los 4 bytes coinciden retorna verdadero
}
