#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

void __interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  switch(bttnState){
  case 2:
    if(++blink_count != 187){ /*187 is 75% of 250*/
      dimLights();
      break;
    }else{
      blink_count = 0;
    }
  case 4:
    if(++blink_count != 125){ /*every half a second annoy the ears of anyone*/
      annoyEars();
      break;
    }else{
      blink_count = 0;
    }
  }
}
