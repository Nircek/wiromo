#include <IRremote.h>
//get it from https://github.com/z3t0/Arduino-IRremote

//TODO: output pins defines

//TODO: input pins defines

//TODO: mode define

//TODO: IR commands defines

void setPins();

//global mode
int gMode=0; //zmienna przechowująca aktualnie włączony tryb
//change mode
void chMode(); //funkcja wywoływana po naciśnięciu przycisku zmiany trybu
void updateModeLED(); //odświerza stan diody trybów
//TODO: functions of loop for each mode

//TODO: functions for motor management

void setup(){
  //setup
  setPins();
  //TODO: begin BT Serial
}

void loop(){
  //loop
  updateModeLED();
  //TODO: switch gMode with cases of modes
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

