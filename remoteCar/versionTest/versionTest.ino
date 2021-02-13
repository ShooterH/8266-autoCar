#include ".\ActionOrders.h"

/*电机组初始化*/
motor groupA;
motor groupB;
//groupA.port = MOTORL;
//groupB.port = MOTORR;

/*使能引脚初始化*/
//groupA.EN = EnableA;
//groupB.EN = EnableB;
void setup()
{
    for(int i=0;i<2;i++)
        pinMode(groupA.com[i],OUTPUT);
    for(int i=0;i<2;i++)
        pinMode(groupB.com[i],OUTPUT);
}
void loop()
{
    GoStraight(groupA,groupB);
    for(int T=3;T>=1;T--)
        Mrun(groupA);Mrun(groupB);
    TurnLeft(groupA,groupB);
    for(int T=1;T>=1;T--)
        Mrun(groupA);Mrun(groupB);
    TurnRight(groupA,groupB);
    for(int T=1;T>=1;T--)
        Mrun(groupA);Mrun(groupB);
}
