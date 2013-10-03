// example fade by PWM


#define LED 9
int i = 0;

void setup()
{
  pinMode(LED, OUTPUT);
}

void loop()
{
  for(; i < 255; i++){
    analogWrite(LED, i);
    delay(10);
  }
  for(; i > 0; i--){
    analogWrite(LED,i);
    delay(10);
  }
}

