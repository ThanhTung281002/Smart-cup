#include "Touch_sensor.h"

Touch_sensor::Touch_sensor(byte pin) {
  this->pin = pin; 

  init(); 
}

void Touch_sensor::init() {
  pinMode(pin, INPUT); 
}


int Touch_sensor::isTouched() {
  int result; 

  int state = digitalRead(pin); 

  if (state == HIGH) {
    result = 1; 
  } else {
    result = 0; 
  }

  return result; 
}