#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

class Touch_sensor {
  private:
    byte pin; 

  public:
    Touch_sensor(byte);
    void init();  
    int isTouched(); 
  

}; 


#endif