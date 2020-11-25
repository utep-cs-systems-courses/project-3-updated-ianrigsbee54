#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"


static char count = 0;
/*as button is pressed we increment to three starting from 0*/
void countToThree()
{
  switch(count){
    /*0*/
  case 0:
    red_on = 0;
    green_on = 0;
    count = 1;
    break;
    
  case 1:
    red_on = 1; /*red for 1*/
    green_on = 0;
    count = 2;
    break;
    
  case 2:
    red_on = 0;
    green_on = 1;/*green for 2*/
    count = 3;
    break;
    
  case 3:
    red_on = 1;
    green_on = 1;/*and both for 3*/
    count = 0;
    break;
  }
  led_changed = 1;/*we update the lights after each break*/
  led_update();
}
/*dims lights to 75%, as we call dimLights() really fast through the wdInterrupt one state
will be off as to achieve the desired effect of 75%*/
void dimLights()
{
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    green_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 1;
    green_on = 1;
    state = 2;
    break;
  case 2:
    red_on = 1;
    green_on = 1;
    state = 3;
    break;
  case 3:
    red_on = 0; /*lights are both off for one state*/
    green_on = 0;
    state = 0;
    break;
  }
  led_changed = 1;/*again update after we change lights*/
  led_update();
}
/*will continuously annoy your ears until the period reaches 0 where it will start all over*/
void annoyEars()
{
  static int period = 1500; /*2000000/1500 = 1333Hz*/ 
  static char annoyanceState = 0;
  switch(annoyanceState){
  case 0:
    period+=200; /*increment the annoying sound*/
    annoyanceState++;
    break;
  case 1:
    period-=450; /*then decrement*/
    annoyanceState = 0;
    break;
  }
  buzzer_set_period(period);
}
/*resets everything, lights will be reset, the count will be reset, but the button will need to be 
  held if you want buzzer to be off*/
void reset()
{
  buzzer_set_period(0);
  count = 0;
  red_on = 0;
  green_on = 0;
  led_changed = 1; /*since we reset everything we have to update lights*/
  led_update();
}

