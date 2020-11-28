#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "statemachines.h"
#include "lcddraw.h"
#include "lcdutils.h"
#define LED_GREEN BIT6

short redrawScreen = 1;

void wdt_c_handler()
{
  static int blinkCount = 0;
  if(++blinkCount == 250){
    blinkCount = 0;
    redrawScreen = 1;
  }
}

void main(){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */
  led_init();
  buzzer_init();
  lcd_int();
  switch_init();
  or_sr(0x8);/* CPU off, GIE on */
  clearScreen(COLOR_BLACK);

  while(1){
    if(redrawScreen){
      switch(buttonState){
      case 1:
	countToThree();
	break;
      case 2:
	break;
	/*i dunno yet*/
      case 3:
	reset();
	break;
      case 4:
	annoyEars();
	break;
      }
      redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
