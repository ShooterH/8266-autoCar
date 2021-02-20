#include ".\ActionOrders.h"

/*电机组初始化*/
motor groupA;
motor groupB;



void setup()
{
    Serial.begin(9600);
    groupA.port[0] = Rin1;
    groupA.port[1] = Rin2;
    groupB.port[0] = Lin1;
    groupB.port[1] = Lin2;
    /*使能引脚初始化*/
    groupA.EN = EnableA;
    groupB.EN = EnableB;
    for(int i=0;i<2;i++){
        pinMode(groupA.port[i],OUTPUT);}
    for(int i=0;i<2;i++){
        pinMode(groupB.port[i],OUTPUT);}
    pinMode(groupA.EN,OUTPUT);
    pinMode(groupB.EN,OUTPUT);
    Serial.println("Initialized");
}
void loop()
{
   GoStraight(groupA,groupB);
   Serial.println("order1 has been written");
    for(int T=3;T>=1;T--){
        Serial.print(groupA.com[0]);
        Serial.println(groupA.com[1]);
        Serial.println(groupA.power);
        Mrun(groupA);Mrun(groupB);
        delay(1000);
        Serial.println(T);}
    TurnLeft(groupA,groupB);
    for(int T=1;T>=1;T--){
        Mrun(groupA);Mrun(groupB);
        delay(1000);}
    TurnRight(groupA,groupB);
    for(int T=1;T>=1;T--){
        Mrun(groupA);Mrun(groupB);
        delay(1000);}
}
