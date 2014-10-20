#include <LiquidCrystal.h>
#include "CountDownTimer.h"
#include "Interval.h"
#include "Button.h"
#include "LED.h"

const int  LCD_Width = 8;
const int  LCD_Height = 2;
const byte  LCDC_delta = 0;

byte LCDC_delta_data[8] = {
B00001,
B00011,
B00011,
B00101,
B01101,
B01001,
B10001,
B11111,
};


//////////////////////////////////////////////////////////////////////////////////////
// Functions


void disp_time(LiquidCrystal& lcd, int h, int m, int s)
{
  lcd.setCursor(0,1);
  if( h < 10 ) lcd.print(" ");
  lcd.print(h);
  lcd.print(":");
  if( m < 10) lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if(s < 10) lcd.print("0");
  lcd.print(s);
}

void disp_rest(LiquidCrystal& lcd, unsigned long dur)
{
   disp_time(lcd, dur/3600, (dur/60)%60, dur%60); 
}

void disp_timer(LiquidCrystal& lcd, CountDownTimer* t)
{
  disp_time(lcd, t->h(), t->m(), t->s());
}

void disp_interval(LiquidCrystal& lcd,  Interval* inter)
{
  lcd.clear();
  lcd.write(LCDC_delta);
  lcd.setCursor(1,0);
  lcd.print("t=");
  lcd.print(inter->str());
  lcd.setCursor(0,1);
  disp_rest(lcd, inter->sec());
}

unsigned long second()
{
  return millis()/1000;
}


//////////////////////////////////////////////////////////////////////////////////////

const unsigned long timer_start_delay = 2000;
const unsigned long chattering_filter = 50;
const unsigned long trigger_length = 2000;

// global variables
LiquidCrystal lcd(12,11,10, 6,7,8,9);
Interval* interval;
unsigned long prev;
Button btn(2);
LED led(5);
LED trigger(4);
CountDownTimer* timer;

//////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  //                                                0        1        2      3        4       5       6        7
  // const char* Interval::interval_strings[] = { "20sec", "1min", "5min", "10min", "30min", "1hr",   "2hr",   "3hr" };
  const int interval_index = 5; // 1 hr
  const int no_change = -1; // 0: off others: on
  interval = new Interval(interval_index, no_change );
  timer = new CountDownTimer(interval->sec());
  lcd.begin(LCD_Width, LCD_Height);
  lcd.createChar(LCDC_delta, LCDC_delta_data);
  lcd.home();
  lcd.noCursor();
  disp_interval(lcd, interval);
  disp_rest(lcd, interval->sec());
  prev = second();
}

//////////////////////////////////////////////////////////////////////////////////////



void loop()
{
  static unsigned long on_time = 0;
  static unsigned long th = 0;
  static unsigned long filter = 0;
  
  unsigned long now = millis();
  unsigned long curr = now / 1000;

  switch(btn.state()){
    case Button::TurnON:
      on_time = now;
      th = on_time + timer_start_delay;
      // チャタリング対策
      filter = on_time + chattering_filter;
      led.on();
    break;

    case Button::TurnOFF:
      if(! timer->is_running()){
        if(filter < now  &&  now < th){
          interval->increase();
          lcd.clear();
          disp_interval(lcd, interval);
        }
      }
      led.off();
      on_time = 0;
    break;

    case Button::ON:
      if(th < now && on_time > 0){
        if(timer->is_ready()){
          timer->reset(interval->sec());
          disp_interval(lcd, interval);
          timer->run();
        }else{
          timer->reset(interval->sec());
          disp_interval(lcd, interval);
        }
        on_time = 0;
        break;
      }
    //break; // fall throgh
    case Button::OFF:
      if(timer->is_done() || timer->rest() > interval->maximum() ){
          disp_interval(lcd, interval);
          timer->reset(interval->sec());
          timer->run();
          trigger.on();
          delay(trigger_length);  // wait for trigger
          trigger.off();
      }
      if(timer->is_running()){
        if(prev != curr){
          disp_timer(lcd, timer);
          led.toggle();
          prev = curr;
        }
      break;
      }
  }
}

