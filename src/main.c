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

short redrawScreen = 1;
void wdt_c_handler()
{
  static int blinkCount = 0;
  if(++blinkCount == 250 && bttnState == 1){/*1.5 seconds*/
    countToThree();
    blinkCount = 0;
    redrawScreen = 1;
  }else if(++blinkCount == 62 && bttnState == 2){
    dim25();
    redrawScreen = 1;
    blinkCount = 0;
  }else if(++blinkCount == 250 && bttnState == 4){
    sirenStateAdvance();
    redrawScreen = 1;
    blinkCount = 0;
  }
}

void main(){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
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
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
