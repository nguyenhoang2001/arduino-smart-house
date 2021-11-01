#include "Arduino.h"
#include "input_processing.h"
#include "input_reading.h"
#include "testing.h"
#include "timer.h"

enum ButtonState { BUTTON_RELEASED , BUTTON_PRESSED ,BUTTON_PRESSED_MORE_THAN_1_SECOND } ;
enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void) {
  switch ( buttonState ){
  case BUTTON_RELEASED:
    if(is_button_pressed(0)) {
      buttonState = BUTTON_PRESSED;
      // INCREASE VALUE OF PORT A BY ONE UNIT
      digitalWrite(led, 1);
    }else {
      digitalWrite(led, 0);
    }
    break;
  case BUTTON_PRESSED:
    if (!is_button_pressed(0)) {
      buttonState = BUTTON_RELEASED;
    } else {
      if( is_button_pressed_1s(0)) {
        buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
      }
    }
    break ;
  case BUTTON_PRESSED_MORE_THAN_1_SECOND :
    if (!is_button_pressed(0)) {
      buttonState = BUTTON_RELEASED ;
    }
    // todo
    
      if(timer_flag1 == 1)  {
        digitalWrite(led, !digitalRead(led));
        setTimer1(2000);
      }
    
    break;
  }
}
