#include "MotorControl.h"
#include "autoAvoid.h"

motor A,B;
void setup()
{
    Serial.begin(9600);
    
    /*马达引脚初始化*/
    A.port[0] = IN1;
    A.port[1] = IN2;
    B.port[0] = IN3;
    B.port[1] = IN4;
    A.EN      = ENA;
    B.EN      = ENB;
    Serial.println("port setup ok");
    
    /*设置引脚为输出模式*/
    A.initilaze();
    B.initilaze();
    sensorInitialize();
    Serial.println("setup ok");
}

void loop()
{
    int *sig = scan();
    if(sig[0] == 0 && sig[1] == 1 && sig[2] == 1 && sig[3] == 0)
    {
        comWr(FORWARD,100,A);
        comWr(FORWARD,100,B);
    }
    if(sig[0] == 0 && sig[1] == 0 && sig[2] == 1 && sig[3] == 1)
    {
        comWr(FORWARD,100,A);
        comWr(FORWARD,30,B);
    }
    if(sig[0] == 1 && sig[1] == 1 && sig[2] == 0 && sig[3] == 0)
    {
        comWr(FORWARD,30,A);
        comWr(FORWARD,100,B);
    }
    if(sig[0] == 0 && sig[1] == 0 && sig[2] == 0 && sig[3] == 0)
    {
        comWr(STOP,100,A);
        comWr(STOP,100,B);
    }
    A.run();
    B.run();
    delete[] sig;
}
