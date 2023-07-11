#include <Wire.h>//LIBRERIA QUE PERSIMTE ESCRIBIR CON EL I2C

 #include <LiquidCrystal_I2C.h>//LIBRERIA PARA LCD

 

 //DEFINIR FILAS Y COLUMNAS DEL LCD CON EL I2C//

 #define lcdAddress 0x27  

 #define filas 2

 #define columnas 16

 LiquidCrystal_I2C lcd(0X27, 16, 2);

 const float Factor = 1.85; // Constante del Factor de Lectura

 int lectura = 0; //Guardar La lectura hecha por el sensor

 const float Factor_1 = 0.185; //Factor de Medicion para lectura de -5A a 5A

 const float Factor_2 = 0.1; //Factor de Medicion para lectura de -20A a 20A

 const float Factor_3 = 0.066; //Factor de Medicion para lectura de -30A a 30A

 int Lectura = 0; // Lectura del pin A////7ds l0

 double Corriente = 0; //Guarda el valor de la corriente leida en el sensor

 float voltajeSensor = 0; //guarda los valores de 0 a 5  

    bool a = 0;

float voltaje;

 void setup() {

   Serial.begin(9600); //Inicializa la comunicacion Serial

 

   lcd.init();

   lcd.backlight();




    attachInterrupt(digitalPinToInterrupt(2),selector,LOW);

    attachInterrupt(digitalPinToInterrupt(3),voltimetro,LOW);

    attachInterrupt(digitalPinToInterrupt(4),muestra,LOW);




 }

 

 void loop() {

 

 

  lcd.setCursor(3,0);

   lcd.print("MULTIMETRO");

   

 




   

   

   lcd.setCursor(3,0);

   lcd.print("CORRIENTE:");

 

   lcd.setCursor(2,1);

   lcd.print(Corriente,3);

 

 

   lcd.setCursor(7,1);

   lcd.print(" AMPERS");

 delay(10000);

   lcd.clear();




  if(a == 1){

    voltimetro();

    a = 0;

  }

 

 

   lcd.setCursor(4,0);

   lcd.print("VOLTAJE:");

 

   lcd.setCursor(3,1);

   lcd.print(voltaje);

 

 

   lcd.setCursor(8,1);

   lcd.print("VOLTS");

 delay(10000);

   lcd.clear();

 

 }




 void amperimetro(){

Lectura = analogRead(A0); //Leer el pin analogico

   voltajeSensor = (Lectura*5.0) / 1023.0; //lectura del sensor    

   Corriente = (voltajeSensor - 2.5)/Factor_1; //Ecuación  para obtener la corriente

   Serial.print("Corriente: ");

   Serial.print(Corriente,3);  

   Serial.println(" AMPS");  

     lcd.setCursor(1,0);

   

 }




  void voltimetro(){

   

   lectura = analogRead(A1); //Para hacer la lectura del pin A0

  voltaje =  (5*lectura*Factor)/1023; // Conversion de lectura analogica a valores de medicion

 Serial.print("Voltaje medido =  ");

 Serial.print(voltaje); // Muestra en el monitor serial la lectura

 Serial.println("V");

 delay(150);




 }




  void muestra(){

 





 }

 void selector(){

   a = 1;

 }