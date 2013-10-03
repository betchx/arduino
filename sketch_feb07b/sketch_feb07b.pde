// example fade by PWM with botton control 


#define LED 9
#define BTN 2
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
}

int getState(void);

// todo impliment
void loop()
{
  analogWrite(LED,getState());
}


int getState(void)
{
  state = digitalRead(BTN);
 
 if(state){
   return 255;
 }
 else 
  return 0;
}

