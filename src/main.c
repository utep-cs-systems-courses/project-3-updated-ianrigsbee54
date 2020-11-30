#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "stateMachines.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "lcdtypes.h"
#define LED_GREEN BIT6

char sirenState = 1;
short redrawScreen = 1;
void wdt_c_handler()
{
  static int blinkCount = 0;
  if(++blinkCount == 250){
    blinkCount = 0;
    redrawScreen = 1;
  }
}
void main(void)
{
  green_on = 1;
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  led_init();
  buzzer_init();
  lcd_init();
  switch_init();
  or_sr(0x8);/* CPU off, GIE on */
  clearScreen(COLOR_BLACK);
  while(1){
    if(redrawScreen){
      redrawScreen = 0;
      switch(bttnState){
      case 1:
	countToThree();
	break;
      case 2:
	dim25();
	break;
      case 3:
	reset();
	break;
      case 4:
	sirenStateAdvance();
	break;
      }
    }
    green_on = 0;
    or_sr(0x10);
    green_on = 1;
  }
}
