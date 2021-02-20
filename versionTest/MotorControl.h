#include"setting.h"


/*命令函数*/
void Mcom(motor &target,const int com[2],int power)
{
    target.com[0] = com[0];
    target.com[1] = com[1];
    target.comWr();
    target.power = power;
}

/*执行函数*/
void Mrun(motor target)
{
    digitalWrite(target.EN,HIGH);
    if (target.power != 100)
    {
        delay(10 * target.power);
        digitalWrite(target.EN,LOW);
    }
}
