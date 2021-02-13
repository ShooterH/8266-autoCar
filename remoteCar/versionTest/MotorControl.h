#include"setting.h"


/*命令函数*/
void Mcom(motor target,int com[2],int power)
{
    target.com = com;
    target.comWr();
    target.power = power;
}

/*执行函数*/
void Mrun(motor target)
{
    digitalWrite(target.EN,HIGH);
    if target.power != 100
    {
        delay(10*power);
        digitalWrite(target.EN,LOW);
    }
}
