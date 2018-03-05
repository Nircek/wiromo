#include <IRremote.h>
//get it from https://github.com/z3t0/Arduino-IRremote

#define MRD     13      //Right Motor Direction
#define MLD     12      //Left Motor Direction
#define MR      11      //Right Motor Speed
#define ML      10      //Left Motor Speed
#define IR      9
//#define IRON    8
#define LED     7       //mode LED
//#define BTON    A0
//#define SLON    5
//#define LFON    4
//#define OFF     3
#define BUTTON  2       //button for changing modes
#define TX      1
#define RX      0

#define SLR     A1
#define SLL     A2
#define LFR     A3
#define LFC     A4
#define LFL     A5

//TODO: mode defines

//TODO: IR commands defines

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

//TODO: functions for motor management

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
}

//function bodys
void setPins(){
  //TODO: set LOW voltage on motors
  //TODO: set pin mode of each pin
  //TODO: enable IR
  //TODO: interrupt connected between button pin and chMode()
}

void chMode(){
  
}
void updateModeLED(){
  
}


void loopBTMode(){
  
}
void loopIRMode(){
  
}
void loopSLMode(){
  
}
void loopLFMode(){
  
}

