#ifndef stateMachine_included
#define stateMachine_included

static char count;
static char dimState;
static char sirenState;
short period;

void countToThree();
void dim25();
short convertperiod(short period);
void siren();
void sirenShapeAdvance();
void sirenStateAdvance();
void reset();

#endif // included
