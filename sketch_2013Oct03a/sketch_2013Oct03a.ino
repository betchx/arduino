#include <Wire.h>
#include <LiquidCrystal.h>

#define BTN 2

#define TURNON  01
#define TURNOFF 10
#define ON  11
#define OFF 00

#define I2CADDRESS 83  //  default value of 7SEG-LED unit(PIC BOOK)

//  2,3,4,5,
LiquidCrystal lcd(12,11,10, 6,7,8,9);
unsigned int cnt = 0;

int btnVal()
{
  return digitalRead(BTN);
}

int btnState()
{
  static int val;
  static int old_val;
  int btn_status;
  val = btnVal();
  btn_status = old_val * 10 + val;
  old_val = val;
  return btn_status;
}


void printHello()
{
  //  lcd.clear();
  //  for(int i=0; i < 0x40; i++)
  //    lcd.print(' ');
  //  lcd.setCursor(0,0);
 if(0){
  lcd.print("Hello");
  lcd.setCursor(0,1); // crlf
  lcd.print("World!");
 }else{
   lcd.print("Hello World!! Hello World!! ");
 }
}

void print7SegLED(unsigned int value)
{
  byte dat[3] = {0,0,0};
  dat[0] = value/256;
  dat[1] = value%256;
  Wire.beginTransmission(I2CADDRESS);
  Wire.write(dat,3);
  Wire.endTransmission();
}


void setup() 
{
  cnt = 0;
  pinMode(BTN,INPUT);
  Wire.begin(I2CADDRESS);
  print7SegLED(cnt);
  lcd.begin(8,2);
  printHello();
}

void loop()
{
  switch(btnState()){
    case OFF:
      cnt += 1;
      print7SegLED(cnt);
      if(cnt%14)
        lcd.scrollDisplayLeft();
      else
        lcd.home();
      break;

//    case TURNOFF:
      //lcd.clear();
      //lcd.print(cnt);
      
    case TURNON:
//      lcd.print(cnt);
      //printHello();
      lcd.clear();
      cnt = 0;
      break;
  }
  delay(1000);
}

