#include".\MotorControl.h"

void TurnLeft(motor,motor);
void TurnRight(motor,motor);
void GoStraight(motor,motor);
void GoBackward(motor,motor);

void TurnLeft(motor left,motor right)
{
    Mcom(left,FORWARD,50);
    Mcom(right,FORWARD,100);
}
void TurnRight(motor left,motor right)
{
    Mcom(left,FORWARD,100);
    Mcom(right,FORWARD,50);
}
void GoStraight(motor left,motor right)
{
    Mcom(left,FORWARD,100);
    Mcom(right,FORWARD,100);
}
void GoBackward(motor left,motor right)
{
    Mcom(left,BACKWARD,1000);
    Mcom(right,BACKWARD,100);
}
