#include".\MotorControl.h"

void TurnLeft(motor &a,motor &b)
{
    Mcom(a,FORWARD,50);
    Mcom(b,FORWARD,100);
}
void TurnRight(motor &a,motor &b)
{
    Mcom(a,FORWARD,100);
    Mcom(b,FORWARD,50);
}
void GoStraight(motor &a,motor &b)
{
    Mcom(a,FORWARD,100);
    Mcom(b,FORWARD,100);
}
void GoBackward(motor &a,motor &b)
{
    Mcom(a,BACKWARD,100);
    Mcom(b,BACKWARD,100);
}
