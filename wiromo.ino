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

#define TBASE   100
#define TMUL    3
#define TBT     TBASE
#define TIR     TBT*TMUL
#define TSL     TIR*TMUL
#define TLF     TSL*TMUL
#define TFI     TLF*TMUL
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
int gMode=TBT; //zmienna przechowująca aktualnie włączony tryb
int gCooldown=0;
//change mode
void chMode(); //funkcja wywoływana po naciśnięciu przycisku zmiany trybu
void updateModeLED(); //odświerza stan diody trybów
void loopBTMode();
void loopIRMode();
void loopSLMode();
void loopLFMode();

#define DRF 0b1000
#define DLF 0b0100
#define DRB 0b0010
#define DLB 0b0001
typedef enum direction{
  NW=0b1000, N=0b1100, NF=0b0100,
  W=0b1001,  O=0b0000,  F=0b0110,
  SW=0b0001, S=0b0011, SF=0b0010  //SE kolidowało z jakąś stałą Arduino
  } direction;
direction gD;
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
    case TBT: loopBTMode(); break;
    case TIR: loopIRMode(); break;
    case TSL: loopSLMode(); break;
    case TLF: loopLFMode(); break;
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
    gMode*=TMUL;
    if(gMode==TFI)gMode=0;
    if(gMode==0)gMode=TBT;
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
  digitalWrite(MRF, (gD&DRF)?HIGH:LOW);
  digitalWrite(MLF, (gD&DLF)?HIGH:LOW);
  digitalWrite(MRB, (gD&DRB)?HIGH:LOW);
  digitalWrite(MLF, (gD&DLF)?HIGH:LOW);
}

void loopBTMode(){
  
}
void loopIRMode(){
  
}
void loopSLMode(){
  
}
void loopLFMode(){
  
}

