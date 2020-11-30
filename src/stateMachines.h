#ifndef stateMachine_included
#define stateMachine_included

static char count;
static char dimState;
char sirenState;
void countToThree();
void dim25();
short convertperiod(short period);
short asPeriod(short pd);
void siren();
void sirenShapeAdvance();
void sirenStateAdvance();
void reset();

#endif // included
