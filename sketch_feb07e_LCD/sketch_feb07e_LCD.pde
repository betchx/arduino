#include <LiquidCrystal.h>

#define BTN 1

#define TURNON  01
#define TURNOFF 10
#define ON  11
#define OFF 00

LiquidCrystal lcd(12,11,10, 2,3,4,5, 6,7,8,9);
int cnt = 0;
int val = 0;
int old_val = 0;

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


void printHello()
{
  lcd.clear();
//  for(int i=0; i < 0x40; i++)
//    lcd.print(' ');
//  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(0,1); // crlf
  lcd.print("World!");
}

void setup() 
{
  pinMode(13,OUTPUT);
//  cnt=0;
  lcd.begin(8,2);
  printHello();
}

void loop()
{
  switch(btnState()){
    case TURNOFF:
      cnt += 1;
      lcd.clear();
      lcd.print(cnt);
      break;
      
    case TURNON:
//      lcd.print(cnt);
      printHello();
      break;
  }
  delay(10);
}

