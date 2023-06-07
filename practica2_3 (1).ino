//brazo robotico
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define pinBuzzer 6
#define reset 2
#define posicion1 7
#define posicion2 8
#define posicion3 9
#define posicion4 10
#define mover_hombro 11
#define mover_brazo 12
#define mover_pinzas 13
Servo hombro;
Servo brazo;
Servo pinzas;
LiquidCrystal_I2C pantalla(0x27, 16, 2);
int lector1;
int lector2;
int lector3;
int lector4;
int lector5;
int lector6;
int lector7;
int lector8;
int grados1;
int grados2;
int grados3;
long hombroDireccion;
long brazoDireccion;
long pinzasDireccion;

 

void setup(){
  Serial.begin(9600);
  pinMode(posicion1,INPUT);
  pinMode(posicion2,INPUT);
  pinMode(posicion3,INPUT);
  pinMode(posicion4,INPUT);
  pinMode(reset,INPUT);
  pantalla.init();
  pantalla.backlight();
  pantalla.clear();
  hombro.attach(3,500,2500);
  brazo.attach(4,500,2500);
  pinzas.attach(5,500,2500);
   attachInterrupt(digitalPinToInterrupt(reset),p_inicial,RISING);  
  }

 

  void loop(){
    lector1 = digitalRead(posicion1);
    lector2 = digitalRead(posicion2);
    lector3 = digitalRead(posicion3);
    lector4 = digitalRead(posicion4);
    lector5 = digitalRead(reset);
    hombroDireccion = analogRead(A0);
    brazoDireccion = analogRead(A1);
    pinzasDireccion = analogRead(A2);
    grados1=map(hombroDireccion,0,1023,0,180);
    Serial.println(hombroDireccion);
    hombro.write(grados1);
    delay(100);
    grados2=map(brazoDireccion,0,1023,0,180);
    grados3=map(pinzasDireccion,0,1023,0,180);
    brazo.write(grados2);
    delay(100);
    pinzas.write(grados3);
    delay(100);
    pantalla.setCursor(0,0);
    pantalla.print(grados1);
    pantalla.setCursor(0,5);
    pantalla.print(grados1);
    pantalla.setCursor(1,0);
    pantalla.print(grados1);

 

if(lector1 == 1){
p_1();
}
if(lector2 == 1){
p_2();
}
if(lector3 == 1){
p_3();
}
if(lector4 == 1){
p_4();
}
if(lector5 == 1){
  uno_();
dos_(); 
tres();
cuatro();
dos_(); 
uno_();
  }
}

 

void p_inicial(){
hombro.write(0);
brazo.write(0);
pinzas.write(0);

  }

 

  
  void p_1(){
hombro.write(40);
brazo.write(20);
pinzas.write(30);
    }
  void p_2(){
  hombro.write(70);
brazo.write(40);
pinzas.write(50);
}
  void p_3(){
  hombro.write(130);
brazo.write(60);
pinzas.write(70);
    }
  void p_4(){
  hombro.write(160);
brazo.write(80);
pinzas.write(90);
delay(1000);   
    }

 

 

//De la cancion
int C_ =  261/2;
int Cs_=  277/2;
int D_ =  293/2 ;
int Ds_=  311/2;
int E_ =  329/2 ;
int F_ =  349/2 ;
int Fs_=  369/2;
int G_ =  391/2 ;
int Gs_=  415/2;
int A_ =  440/2 ;
int As_=  466/2;
int B_ =  493/2 ;
int Sil = 5;
int C =  261;
int Cs=  277;
int D =  293 ;
int Ds=  311;
int E =  329 ;
int F =  349 ;
int Fs=  369;
int G =  391 ;
int Gs=  415;
int A =  440 ;
int As=  466;
int B =  493 ;
int C2   =524;
int Cs2  =555;
int D2   =588;
int Ds2  =623;
int E2   =660;
int F2   =699;
int Fs2  =740;
int G2   =784;
int Gs2  =831;
int A_2   = 880;
int As2  =933;
int B2   =988;
int C3  =1047;
int Cs3  =555*2;
int D3   =588*2;
int Ds3  =623*2;
int E3   =660*2;
int F3   =699*2;
int Fs3  =740*2;
int G3   =784*2;
int Gs3  =831*2;
int A_3   = 880*2;
int As3  =933*2;
int B3   =988*2;
int tempo=112*2;
int negra=60000/tempo;
int semi = negra/4;
//int semi =86;
int corch = 2*semi;
//int negra = corch*2;
int np = corch*3;
int blanca = negra*2;
int redonda = blanca*2;
int rep = 3*negra;
int bnp = 3*negra+3*corch;
int retardo = 100;
void nota(int nota, int duracion){
  tone(pinBuzzer,nota, duracion);
  delay(duracion);
  noTone(pinBuzzer);
  delay(duracion);
}
//fin del programa de la cancion
  //de la cancion tambien
  void prePre(){
  nota(A   , semi );
  nota(A_   , semi );
  nota(C2  , semi);  
  nota(A_   , semi );
  nota(B   , semi );
  nota(A_   , semi );
  nota(C2  , semi);  
  nota(E2 , semi);  
  nota(A_   , semi );
  nota(A   , semi );
  nota(C2  , semi);  
  nota(A_   , semi );
  nota(B   , semi );
  nota(Sil , semi);  
  nota(C2  , semi);  
  nota(A   , semi );
  nota(A_   , semi );
  nota(A   , semi );
  nota(C2   , semi );
  nota(A_   , semi );
  nota(B   , semi );
  nota(A_   , semi );
  nota(C2   , semi );
  nota(E2   , semi );
  nota(A_   , semi );
  nota(A   , semi );
  nota(C2   , semi );
  nota(A_   , semi );
  nota(B   , semi );
  nota(A_   , semi );
  nota(C2   , semi );
nota(A_   , semi );
}
void uno_(){
  nota(E   , semi );
  nota(E_   , semi );
  nota(G   , semi );
  nota(E_   , semi );
  nota(Fs   , semi );
  nota(E_   , semi );
  nota(G   , semi );
  nota(B   , semi );
  nota(E_   , semi );
  nota(E   , semi );
  nota(G   , semi );
  nota(E_   , semi );
  nota(Fs   , semi );
  nota(E_   , semi );
  nota(G   , semi );
  nota(E   , semi );
  nota(E_   , semi );
  nota(E   , semi );
  nota(G   , semi );
  nota(E_   , semi );
  nota(Fs   , semi );
  nota(E_   , semi );
  nota(G   , semi );
  nota(B   , semi );
  nota(E_   , semi );
  nota(E   , semi );
  nota(G   , semi );
  nota(E_   , semi );
  nota(Fs   , semi );
  nota(E_   , semi );
  nota(G   , semi );
  nota(E_   , semi ); 
}
void dos_(){
  nota( F  , semi );
  nota( F_ , semi );
  nota( A  , semi );
  nota( F_ , semi );
  nota(G , semi);
  nota(F_, semi);
  nota(A , semi);
  nota(C2, semi);
  nota( F_ , semi );
  nota( F  , semi );
  nota( A  , semi );
  nota( F_ , semi );
  nota( G, semi);
  nota( F_ , semi );
  nota( A  , corch );
    nota(G , semi);
    nota(G_ , semi);
    nota(B , semi);
    nota(G_ , semi);
    nota(A , semi);
    nota(G_ , semi);
    nota(B , semi);   
    nota(D2 , semi);
    nota(G_ , semi);
    nota(G , semi);
    nota(B , semi);
    nota(G_ , semi);
    nota(A , semi);
    nota(G_ , semi);
    nota(B , corch);
}
void tres(){
  nota(D , semi);
  nota(D_ , semi);
  nota(F , semi);
  nota(D_ , semi);
  nota(E , semi);
  nota(D_ , semi);
  nota(F , semi);
  nota(A , semi);
  nota(D_ , semi);
  nota(D , semi);
  nota(F , semi);
  nota(D_ , semi);
  nota(E , semi);
  nota(D_ , semi);
  nota(F , corch);
}
void cuatro(){
  nota(E , semi);
  nota(E_ , semi);
  nota(G , semi);
  nota(E_ , semi);
  nota(Fs , semi);
  nota(E_ , semi);
  nota(G , semi);
  nota(B , semi);
  nota(E_ , semi);
  nota(E , semi);
  nota(G , semi);
  nota(E_ , semi);
  nota(Fs , semi);
  nota(E_ , semi);
  nota(G , corch);
  }
  //fin del programa