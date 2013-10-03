

#define VEL 250 // speed of train (km/h)
#define INIT_BLANK 2 // sec
#define INTERVAL 10 // sec
#define TURNON_DUR 5 // usec

#define OUTPIN 13


unsigned long timingList[200];
int ntiming;
int condition = LOW;


void setup()
{
  ntiming = 0;
  unsigned long axint[] = {2500UL, 15000UL, 2500UL, 5000UL};
// 75m/sec (=75mm/msec) for 270km/h
// axint / 75 ==> msec for 270km/h
// axint / 75 * 270 / 250 ==> msec for 250km/h
  for(int i = 0; i < 4; i++){
    axint[i] *= 270UL;
    axint[i] /= (VEL*75);
    if(axint[i] < 10UL)
      axint[i] = 10;
  }
  
  timingList[ntiming++] = INIT_BLANK*1000; // append to first
  for(int car = 0; car < 16; car++){
    for(int axis = 0; axis < 4; axis++){
      timingList[ntiming++] = TURNON_DUR;
      timingList[ntiming++] = axint[axis] - TURNON_DUR;
    }
  }
  timingList[ntiming-1] += INTERVAL * 1000;
  
  pinMode(OUTPIN,OUTPUT);
  digitalWrite(OUTPIN,LOW);
}

void swap_condition()
{
    if(condition == HIGH){
      condition = LOW;
    }else{
      condition = HIGH;
    }
}

void loop()
{
  delay(timingList[0]);
  while(1)
  {
    for(int it = 1; it < ntiming; it++){
      swap_condition();
      digitalWrite(OUTPIN,condition);
      delay(timingList[it]);
    }
  }
}

