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

//TODO: definicje trybów

//TODO: defincje komend IR'a

void setPins();

//global mode
int gMode=0; //zmienna przechowująca aktualnie włączony tryb
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
    case 1: loopBTMode(); break;
    case 2: loopIRMode(); break;
    case 3: loopSLMode(); break;
    case 4: loopLFMode(); break;
  }
  updateMotors();
}

//function bodys
void setPins(){
  //TODO: ustawić niskie napięcie na silnikach
  //TODO: ustawić tryby każdego pinu
  //TODO: uruchomić IR
  //TODO: przerwanie między pinem przycisku i chMode()
}

void chMode(){
  
}
void updateModeLED(){
  
}

void updateMotors(){
  
}

void loopBTMode(){
  
}
void loopIRMode(){
  
}
void loopSLMode(){
  //branch for SL programming
}
void loopLFMode(){
  
}

