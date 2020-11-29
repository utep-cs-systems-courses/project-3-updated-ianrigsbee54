#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

static char count = 0;
static char sirenState = 0;
short period = 1500;
static char dimState = 0;
/*as button is pressed we increment to three starting from 0*/
void countToThree()
{
  switch(count){
    /*0*/
  case 0:
    drawString8x12(20, 10,"0", COLOR_WHITE, COLOR_BLACK);
    count = 1;
    break;
    
  case 1:
    drawString8x12(20, 30,"1", COLOR_WHITE, COLOR_BLACK);
    count = 2;
    break;
    
  case 2:
    drawString8x12(20, 50, "2", COLOR_WHITE, COLOR_BLACK);
    count = 3;
    break;
    
  case 3:
    drawString8x12(20, 70, "3", COLOR_WHITE, COLOR_BLACK);
    count = 0;
    break;
  }
  clearScreen(COLOR_BLACK);
}

/*dims lights to 75%, as we call dimLights() really fast through the wdInterrupt one state
will be off as to achieve the desired effect of 75%*/

short convertPeriod(short period)
{
  return 2000000/period;
}
/*will continuously annoy your ears until the period reaches 0 where it will start all over*/
void siren()
{
  switch(sirenState){
  case 0:
    period+=200; /*increment the annoying sound*/
    sirenState++;
    break;
  case 1:
    period-=200; /*then decrement*/
    sirenState = 0;
    break;
  default:
    sirenState = -1;
    buzzer_set_period(0);
    break;
  }
  short sirenHz = convertPeriod(period);
  buzzer_set_period(sirenHz);
}
void sirenShapeAdvance()
{
  switch(sirenState){
  case 0:
    drawPyramid(screenWidth/2, 0);
    break;
  case 1:
    drawPyramid(screenWidth/2, 1);
    break;
  }
}
void sirenStateAdvance()
{
  switch(sirenState){
  case 0:
    siren();
    sirenShapeAdvance;
    sirenState++;
    break;
  case 1:
    siren();
    sirenShapeAdvance;
    sirenState--;
    break;
  }
}
/*resets everything, lights will be reset, the count will be reset, but the button will need to be 
  held if you want buzzer to be off*/
void reset()
{
  clearScreen(COLOR_BLACK);
  bttnState = 0;
  buzzer_set_period(0);
  count = 0;
  red_on = 0;
  led_changed = 1; /*since we reset everything we have to update lights*/
  led_update();
}
void dim25()
{
  switch(dimState){
  case 0:
    red_on = 1;
    dimState++;
    break;
  case 1:
    dimState++;
  case 2:
    dimState++;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_update();
}
