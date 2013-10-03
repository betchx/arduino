#include <Wire.h>

// example fade by PWM with botton control 


#define LED 9
#define BTN 2

#define TURNON  01
#define TURNOFF 10
#define ON  11
#define OFF 00

#define I2CADDRESS 83  //  default value of 7SEG-LED unit(PIC BOOK)

int i = 0;
int val = 0;      //current value for LED
int old_val = 0;  //previous value for LED
int state = 0;  // 0:OFF

int brightness = 0; // current brightness of LED
unsigned long startTime = 0;  // time when the button push down.

// initialize the board
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  Wire.begin();
  Serial.begin(9600);
}

int getState(void);

// todo impliment
void loop()
{
  analogWrite(LED,getState());
}

int btnVal()
{
  return digitalRead(BTN);
}

int btnState()
{
  int btn_status;
  val = btnVal();
  btn_status = old_val * 10 + val;
  old_val = val;
  return btn_status;
}

void swapState(){
    state = 1 - state;
}

void resetStatTime(){
    startTime = millis();
}

void printSerial()
{
  Serial.println(brightness);
}

void print7SegLED()
{
  byte dat[3] = {0,0,0};
  if(state){
    dat[1] = brightness;
  }
  Wire.beginTransmission(I2CADDRESS);
  Wire.send(dat,3);
  Wire.endTransmission();
  printSerial();
}

int getState(void)
{
  switch(btnState()){
   case TURNON:
    swapState();
    resetStatTime();
    print7SegLED();
    delay(10);
    break;
   case ON:
    if(state){
     if(millis() - 500 > startTime){
       brightness+=1;
       brightness %= 255;
       delay(10);
     }
    }
    print7SegLED();
    break;
   case TURNOFF:
    print7SegLED();
    break;
   case OFF:
    // do nothing (does not send data by I2C)
    break;
  }
  if(state)
    return brightness;
  else 
    return 0;
}

