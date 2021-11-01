#include "Arduino.h"
#include "timer.h"
#include "testing.h"
#include "input_reading.h"

void setTimer0(int duration) {
  timer_count = duration / 10;
  timer_flag0 = 0;
}

void setTimer1(int duration) {
  timer_count1 = duration / 10;
  timer_flag1 = 0;
}

void timer_run() {
  if(timer_count > 0) {
    timer_count = timer_count - 1;
    if(timer_count == 0)
      timer_flag0 = 1;
  }
  if(timer_count1 > 0) {
    timer_count1 = timer_count1 - 1;
    if(timer_count1 == 0)
      timer_flag1 = 1;
  }
}

void time_init() {
  TCCR1A = 0;
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
  TCNT1 = t1_load;
  OCR1A = t1_cmp;
  TIMSK1 = (1<<OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = t1_load;
  button_reading();
  timer_run();
}
