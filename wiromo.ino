#include <IRremote.h>
//weź ją stąd https://github.com/z3t0/Arduino-IRremote

#define MRF     13      //Right Motor Forward
#define MLF     12      //Left Motor Forward
#define MRB     11      //Right Motor Backward
#define MLB     10      //Left Motor Backward
#define IR      9
#define LED     7       //dioda trybu
#define BUTTON  2       //przycisk do zmiany trybów
#define TX      1       //pin do BT
#define RX      0       //pin do BT

#define SLR     A0      //sensor ŚwiatłoLuba Prawy
#define SLL     A1      //sensor ŚwiatłoLuba Prawy
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
  pinMode(MRF,OUTPUT);
  pinMode(MLF,OUTPUT);
  pinMode(MRB,OUTPUT);
  pinMode(MLB,OUTPUT);
  digitalWrite(MRF,LOW);
  digitalWrite(MLF,LOW);
  digitalWrite(MRB,LOW);
  digitalWrite(MLB,LOW);
  
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
  unsigned long time=millis();
  time%=2*gMode;
  digitalWrite(LED,time>gMode);
}

void updateMotors(){
  if(gML>0){digitalWrite(MLF,HIGH);digitalWrite(MLB, LOW);}
  else if(gML==0){digitalWrite(MLF,LOW);digitalWrite(MLB, LOW);}
  else{digitalWrite(MLF, LOW);digitalWrite(MLB, HIGH);}
  if(gMR>0){digitalWrite(MRF,HIGH);digitalWrite(MRB, LOW);}
  else if(gMR==0){digitalWrite(MRF,LOW);digitalWrite(MRB, LOW);}
  else{digitalWrite(MRF, LOW);digitalWrite(MRB, HIGH);}
}

void loopBTMode(){
  
}
void loopIRMode(){
  
}
void loopSLMode(){
  
}
void loopLFMode(){
  
}

