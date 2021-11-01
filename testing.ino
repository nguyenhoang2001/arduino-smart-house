#include "timer.h"
#include "dht_lcd.h"
#include "testing.h"
#include "input_processing.h"

int timer_flag0 = 0;
int timer_count = 0;
int timer_flag1 = 0;
int timer_count1 = 0;
// The main set up
void setup()
{
  // put your setup code here, to run once:
  setTimer0(1000);
  setTimer1(2000);
  time_init();
  dht_lcd_init();
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

// The main loop
void loop()
{
  // put your main code here, to run repeatedly:
  if (timer_flag0 == 1)
  {
    dht_lcd_func();
    setTimer0(1000);
  }
  fsm_for_input_processing();
  //  int pinValue = digitalRead(button);
  //  delay(10);
  //  if(buttonStatus!= pinValue) {
  //    buttonStatus = pinValue;
  //    digitalWrite(led, !digitalRead(led));
  //  }
}
