#ifndef COUNT_DOWN_TIMER_H
#define COUNT_DOWN_TIMER_H
#include "Arduino.h"

class CountDownTimer
{
  unsigned long start_time;
  unsigned long end_time;
  unsigned long dur;
  enum TimerState
  {
     INIT, READY, RUNNING, SUSPEND, FINISHED
  };
  

public:

  CountDownTimer(unsigned long duration_in_sec = 0)
  {
    reset(duration_in_sec);
  }
  void reset(unsigned long duration = 0)
  {
    if(duration > 0)
      dur = duration * 1000;
    start_time = 0;
  }
  void run()
  {
    start_time = millis();
    end_time = dur + start_time;
  }
  
  void terminate()
  {
    start_time = 0;
    end_time = millis();
  }
  
  TimerState check()const
  {
    unsigned int now = millis();
    if(start_time == 0){
      if(dur > 0){
        return  READY;
      }else{
        return  INIT;
      }
    }
    if(now > end_time)  return FINISHED;
    return  RUNNING;
  }
  
  // 残り時間　ミリ秒
  unsigned long ms_rest() const {return end_time - millis(); }
  unsigned long rest()const{ return ms_rest() / 1000; }
  unsigned long s()const{  return (rest()          ) % 60;  }
  unsigned long m()const{  return (rest() / 60     ) % 60;  }
  unsigned long h()const{  return (rest() / 60 / 60) % 60;  }
  boolean is_up()const{ return check() == FINISHED ; }
  boolean is_finished()const{ return check() == FINISHED ; }
  boolean is_done()const{ return check() == FINISHED ; }
  boolean is_running()const{  return check() == RUNNING;}
  boolean can_be_start()const{return check() == READY;}
  boolean is_ready()const{return check() == READY;}

};

#endif
