#ifndef INTERVAL_H
#define INTERVAL_H
#include "Arduino.h"

class Interval
{
  static const char* interval_strings[];// = { "1min", "5min", "10min", "30min", "1hr",   "2hr",   "3hr" };
  static const unsigned long intervals_in_sec[];//    = {     60,  5*60 ,  10*60 ,  30*60 , 60*60, 2*60*60, 3*60*60 };
  static const int size_ ;//= sizeof(intervals_in_sec) / sizeof(int);
  static const int ubound;// = size_ - 1;
  int index;
  int constant;

public:
  // construct
  Interval(int index_ = 0, int constant_ = 0 )
  {
    index = index_;
    constant = constant_;
  }
  
  // 間隔を表す文字列を返す
  const char* str()
  {
    return interval_strings[index];
  }
  // 秒単位で返す
  unsigned long sec(){
    return intervals_in_sec[index];
  }
  // ミリ秒単位で返す
  unsigned long millis()
  {
    return sec() * 1000;
  }
  // 増やす
  void increase()
  {
    if(constant == 0){
      index = (index + 1)  % size_;
    }
  }
  // 減らす
  void decrease()
  {
    if(constant ==0){
      if(index > 0){
        --index;
      }else{
        index = size_ - 1;
      }
    }
  }
  
  unsigned long maximum()const{return intervals_in_sec[size_ - 1];}
};


const char* Interval::interval_strings[] = { "20sec", "1min", "5min", "10min", "30min", "1hr",   "2hr",   "3hr" };
const unsigned long Interval::intervals_in_sec[]  = {  20,   60,  5*60 ,  10*60 ,  30*60 , 60*60, 2*60*60, 3*60*60 };
const int Interval::size_ = 8; //  sizeof(intervals_in_sec) / sizeof(int);

#endif

