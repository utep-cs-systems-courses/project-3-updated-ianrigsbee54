#ifndef stateMachine_included
#define stateMachine_included

char count;
char buttonState;
int sirenState;
short period;

void countToThree();
void changeButtonState(char bttn);
short convertperiod(short period);
void dimLights();
void annoyEars();
void reset();

#endif // included
