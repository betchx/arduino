#ifndef BUTTON_H
#define BUTTON_H
#include "Arduino.h"

class Button
{
  unsigned pin;

public:
  Button(unsigned pin_number = 2): pin(pin_number)
  {
    pinMode(pin, INPUT);
  }
//  enum Status {  OFF = 0, TurnON = 1, TurnOFF=10, ON = 11};
  enum Status {  OFF = 11, TurnON = 10, TurnOFF=1, ON = 00};
  
  int value()const{return digitalRead(pin); }
  
  Status state()const{
    static int val;
    static int old;
    Status res;
    val = value();
    res = (Status)(old * 10 + val);
    old = val;
    return res;
  }
};

#endif
