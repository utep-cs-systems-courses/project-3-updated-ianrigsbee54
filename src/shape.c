#include <msp430.h>
#include "shape.h"
/*
int compare(u_char a, u_char b)
{
  if(a <= b){
    return 1;
  }else{
    return 0;
  }
}
*/
 /*draws a pyramid*/
void drawPyramid(u_char center, u_int state)
{
  if(state == 1){
    for(u_char r = 0; r < 15; r++){
      for(u_char c = 0; compare(c,r); c++){
	drawPixel(center + c, r, COLOR_BLUE);
	drawPixel(center - c, r, COLOR_BLUE);
      }
    }
  }else{
    for(u_char r = 0; r < 15; r++){
      for(u_char c = 0; c <= r; c++){
	drawPixel(center + c, r, COLOR_RED);
	drawPixel(center - c, r, COLOR_RED);
      }
    }
  }
}
