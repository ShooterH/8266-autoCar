#include "setting.h"
/*该头文件定义了有关减速电机驱动的函数*/
const int FORWARD[] ={0,1};
const int BACKWARD[]={1,0};
const int STOP[]    ={0,0};

/*引脚定义
  在setting.h中设置你的引脚*/
int left1  = MOTORL1;
int left2  = MOTORL2;
int right1 = MOTORR1;
int right2 = MOTORR2;
int ENA    = EnableA;
int ENB    = EnableB;

void Mcom(int status[2],int Power,int Motor)
{
    /*status为命令类型，包含前进，后退，制动*/
    /*power为电机调速变量，原理为PWM脉冲，输入范围为1-100（满速）*/
    /*Motor为要操控的电机，分别对应AB马达，输入变量ENA或ENB*/

    /*状态写入*/
    digitalWrite(lef1,status[0]);
    digitalWrite(lef2,status[1]);
    digitalWrite(right1,status[0]);
    digitalWrite(right2,status[1]);

    /*PWM部分*/
    /*int Period = 10*Power;
    while(!newComREc)
    {
        digitalWrite()
    }*/
}

void Mrun(int Power[2])
{
    int Tmin,Tmax
    if(Power[0]>=Power[1])
    {
        Tmin = 10*Power[1];
        Tmax = 10*Power[0];
    }
    else
    {
        Tmin = 10*Power[0];
        Tmax = 10*Power[1];
    }
    
    while(!newComRec)
    {
        //TODO
    }
}