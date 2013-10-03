#ifndef LED_H
#define LED_H
#include "Arduino.h"
class LED
{
  int pin;
  boolean high;
public:
  LED(int pin_number):pin(pin_number),high(false)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  void on(){ digitalWrite(pin, HIGH); high = true;}
  void off(){ digitalWrite(pin, LOW); high = false;}
  void toggle(){ 
    if(high){
      off();
    }else{
      on();
    }
  }
  void set(int val)
  {
    digitalWrite(pin, val);
  }
};

#endif

