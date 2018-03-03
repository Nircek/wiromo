#include <IRremote.h>
//get it from https://github.com/z3t0/Arduino-IRremote

//output pins defines

//input pins defines

//mode define

//IR commands defines

//function definitions with their globals
void setPins();

//global mode
int gMode=0; //zmienna przechowująca aktualnie włączony tryb
//change mode
void chMode(); //funkcja wywoływana po naciśnięciu przycisku zmiany trybu
void updateModeLED(); //odświerza stan diody trybów


void setup(){
  //setup
  setPins();
}

void loop(){
  //loop
  updateModeLED();
}

//function bodys
void setPins(){
  //interrupt connected between button pin and chMode()
}

void chMode(){
  
}
void updateModeLED(){
  
}

