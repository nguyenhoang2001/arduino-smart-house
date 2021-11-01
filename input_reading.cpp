#include "input_reading.h"
#include "testing.h"
#include "Arduino.h"

// we aim to work with more than one buttons
# define N0_OF_BUTTONS             1

// timer interrupt duration is 10ms , so to pass 1 second ,
// we need to jump to the interrupt service routine 100 time
# define DURATION_FOR_AUTO_INCREASING     10
# define BUTTON_IS_PRESSED          0
# define BUTTON_IS_RELEASED         1

static int buttonBuffer[ N0_OF_BUTTONS ] = {1};
// we define two buffers for debouncing
static int debounceButtonBuffer1[ N0_OF_BUTTONS ] = {1};
static int debounceButtonBuffer2[ N0_OF_BUTTONS ] = {1};

static uint8_t flagForButtonPress1s[ N0_OF_BUTTONS ] = {0};

// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
static uint16_t counterForButtonPress1s[ N0_OF_BUTTONS ] = {0};

void button_reading() {

  for (char i = 0; i < N0_OF_BUTTONS; i++) {
    debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
    debounceButtonBuffer1[i] = digitalRead(button);

    if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
      buttonBuffer[i] = debounceButtonBuffer1[i];

    if( buttonBuffer[i] == BUTTON_IS_PRESSED ) {
      // if a button is pressed , we start counting

      if( counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING ) {
        counterForButtonPress1s[i]++;
      }
      else {
        // the flag is turned on when 1 second has passed
        // since the button is pressed.
        flagForButtonPress1s[i] = 1;
        // todo
      }
    }
    else {
      counterForButtonPress1s[i] = 0;
      flagForButtonPress1s[i] = 0;
    }
  }
}

unsigned char is_button_pressed( uint8_t index ) {
  if( index >= N0_OF_BUTTONS ) return 0;
  return ( buttonBuffer[index] == BUTTON_IS_PRESSED ) ;
}

unsigned char is_button_pressed_1s( unsigned char index ) {
  if( index >= N0_OF_BUTTONS ) return 0xff ;
  return ( flagForButtonPress1s [index] == 1) ;
}
