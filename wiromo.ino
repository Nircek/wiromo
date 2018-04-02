#include <IRremote.h>
//weź ją stąd https://github.com/z3t0/Arduino-IRremote
#include <SoftwareSerial.h>

#define MRF     13      //Right Motor Forward
#define MRB     12      //Right Motor Backward
#define MLF     11      //Left Motor Forward
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
#define IRCNW   0xFF30CF
#define IRCN    0xFF18E7
#define IRCNF   0xFF7A85
#define IRCW    0xFF10EF
#define IRCO    0xFF38C7
#define IRCF    0xFF5AA5
#define IRCSW   0xFF42BD
#define IRCS    0xFF4AB5
#define IRCSF   0xFF52AD


void setPins();

//global mode
int gMode=TBT; //zmienna przechowująca aktualnie włączony tryb
unsigned long gCooldown=0;
//change mode
void chMode(); //funkcja wywoływana po naciśnięciu przycisku zmiany trybu
void updateModeLED(); //odświerza stan diody trybów
unsigned long BTrefresh=0;//moment w czasie, kiedy robot ma przestać jechać na krótkim
int BTreftime=1000;//czas, przez który robot ma jechać na krótkim
void loopBTMode();
void loopIRMode();
void loopSLMode();
void loopLFMode();

SoftwareSerial mySerial(5, 6); // RX, TX

#define DRF 0b1000
#define DRB 0b0100
#define DLF 0b0010
#define DLB 0b0001
typedef enum direction{
  NW=0b1000, N=0b1010, NF=0b0010,
  W=0b1001,  O=0b0000,  F=0b0110,
  SW=0b0001, S=0b0101, SF=0b0100  //SE kolidowało z jakąś stałą Arduino
  } direction;
direction gD;
direction BTdef=O; //BT default ; kierunek, w który zmierza robot na długim
void updateMotors();  //funkcja zmieniająca rzeczywiste napięcie

void setup(){
  //setup
  setPins();
  Serial.begin(9600);
  mySerial.begin(9600);
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
  digitalWrite(MLB, (gD&DLB)?HIGH:LOW);
  
  Serial.print((gD&DRF)?HIGH:LOW);
  Serial.print((gD&DLF)?HIGH:LOW);
  Serial.print((gD&DRB)?HIGH:LOW);
  Serial.println((gD&DLB)?HIGH:LOW);
}

void loopBTMode(){
  if(millis()>BTrefresh)gD=BTdef;
  if(mySerial.available()>0){
    char c=mySerial.read();
    Serial.println(c);
    mySerial.println(c);
    bool dlugi=c<'a';//jeżeli istnieje ASCII to łapie tylko duże litery
    c=dlugi?c:c-('a'-'A');//toUpperCase
    switch(c){
      /*Q W S
         qwe
        AaSdD  H
         zxc   L
        Z X C*/
      case 'Q': gD=NW; break;
      case 'W': gD=N;  break;
      case 'E': gD=NF; break;
      case 'A': gD=W;  break;
      case 'S': gD=O;  break;
      case 'D': gD=F;  break;
      case 'Z': gD=SW; break;
      case 'X': gD=S;  break;
      case 'C': gD=SF; break;
      case 'H': BTreftime+=100;break;
      case 'L': BTreftime-=100;break;
    }
    if(!dlugi)BTrefresh=millis()+BTreftime;
    else BTdef=gD;
  }
}
void loopIRMode(){
  if (ir.decode(&IRres)){
    Serial.print(IRres.value, HEX);
    switch(IRres.value){
      case -1:    Serial.println();               break;
      case IRCNW: Serial.println("(NW)"); gD=NW;  break;
      case IRCN:  Serial.println("(N)");  gD=N;   break;
      case IRCNF: Serial.println("(NF)"); gD=NF;  break;
      case IRCW:  Serial.println("(W)");  gD=W;   break;
      case IRCO:  Serial.println("(O)");  gD=O;   break;
      case IRCF:  Serial.println("(F)");  gD=F;   break;
      case IRCSW: Serial.println("(SW)"); gD=SW;  break;
      case IRCS:  Serial.println("(S)");  gD=S;   break;
      case IRCSF: Serial.println("(SF)"); gD=SF;  break;
      default:    Serial.println();       gD=O;   break;
    }
    ir.resume();
    delay(100);
  }
}
void loopSLMode(){
  
}
void loopLFMode(){
  
}

