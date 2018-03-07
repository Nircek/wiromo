#include <IRremote.h>
//weź ją stąd https://github.com/z3t0/Arduino-IRremote

#define MRD     13      //Right Motor Direction - kierunek obrotu prawego silnika
#define MLD     12      //Left Motor Direction - kierunek obrotu lewego silnika
#define MR      11      //Right Motor Speed - prędkość obrotu prawego silnika
#define ML      10      //Left Motor Speed - prędkość obrotu lewego silnika
#define IR      9
//#define IRON    8
#define LED     7       //dioda trybu
//#define BTON    A0
//#define SLON    5
//#define LFON    4
//#define OFF     3
#define BUTTON  2       //przycisk do zmiany trybów
#define TX      1       //pin do BT
#define RX      0       //pin do BT

#define SLR     A1      //sensor ŚwiatłoLuba Prawy
#define SLL     A2      //sensor ŚwiatłoLuba Prawy
#define LFR     A3      //sensor LineFollowera Prawy
#define LFC     A4      //sensor LineFollowera Środkowy
#define LFL     A5      //sensor LineFollowera Lewy

#define MBASE   100
#define MMUL    3
#define MBT     MBASE
#define MIR     MBT*MMUL
#define MSL     MIR*MMUL
#define MLF     MSL*MMUL
#define MFI     MLF*MMUL
#define BCD     500     //Button CoolDown

IRrecv ir(IR);
decode_results IRres;
#define IRCUP     0x000000
#define IRCDOWN   0x000000
#define IRCLEFT   0x000000
#define IRCRIGHT  0x000000
#define IRCSTOP   0x000000

void setPins();

//global mode
int gMode=MBT; //zmienna przechowująca aktualnie włączony tryb
int gCooldown=0;
//change mode
void chMode(); //funkcja wywoływana po naciśnięciu przycisku zmiany trybu
void updateModeLED(); //odświerza stan diody trybów
void loopBTMode();
void loopIRMode();
void loopSLMode();
void loopLFMode();

int gML=0;  //napięcie na lewym silniku (dodatnie - do przodu, ujemne - do tyłu)
int gMR=0;  //napięcie na prawym silniku (dodatnie - do przodu, ujemne - do tyłu)
void updateMotors();  //funkcja zmieniająca rzeczywiste napięcie

void setup(){
  //setup
  setPins();
  //TODO: begin BT Serial
}

void loop(){
  //loop
  updateModeLED();
  switch(gMode){
    case MBT: loopBTMode(); break;
    case MIR: loopIRMode(); break;
    case MSL: loopSLMode(); break;
    case MLF: loopLFMode(); break;
  }
  updateMotors();
}

//function bodys
void setPins(){
  pinMode(MR,OUTPUT);
  pinMode(ML,OUTPUT);
  digitalWrite(MR,LOW);
  digitalWrite(ML,LOW);
  
  pinMode(MRD,OUTPUT);
  pinMode(MLD,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);
  pinMode(SLL,INPUT);
  pinMode(SLR,INPUT);
  pinMode(LFL,INPUT);
  pinMode(LFC,INPUT);
  pinMode(LFR,INPUT);

  ir.enableIRIn();
  
  attachInterrupt(digitalPinToInterrupt(BUTTON), chMode, RISING);
}

void chMode(){
  if(millis()-gCooldown>BCD){
    gMode*=3;
    if(gMode==MFI)gMode=0;
    if(gMode==0)gMode=MBT;
    Serial.println(gMode);
    gCooldown=millis();
  }else Serial.println("COOLDOWN");
}
void updateModeLED(){
  
}

void updateMotors(){
  
}

void loopBTMode(){
  //to jest gałąź 'master'
  //jeżeli chcesz edytować tutaj kod idź do gałęzi 'BT-programming'
}
void loopIRMode(){
  //to jest gałąź 'master'
  //jeżeli chcesz edytować tutaj kod idź do gałęzi 'IR-programming'
}
void loopSLMode(){
  //to jest gałąź 'master'
  //jeżeli chcesz edytować tutaj kod idź do gałęzi 'SL-programming'
}
void loopLFMode(){
  //to jest gałąź 'master'
  //jeżeli chcesz edytować tutaj kod idź do gałęzi 'LF-programming'
}

