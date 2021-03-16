# 目录
1. 开始之前
    1. Arduino
    1. 乐鑫科技
    1. 原理简介
1. 开始制作
    1. 所需材料
    1. 代码编写
        1. 代码节选
    3. 安装
1. 总结 
1. 附录
    1. 项目代码
    1. 附图
-----

# 1.开始之前
## 1.1 Arduino
        Arduino is an open source hardware and software company and maker community. Arduino started in the early 2000s. Popular with electronic makers, Arduino offers a lot of flexibility through an open source system.
## 1.2 乐鑫科技
        乐鑫科技是一家全球化的无晶圆厂半导体公司，成立于 2008 年，总部位于中国上海，在大中华地区、新加坡、印度、捷克和巴西都设立了研发中心。乐鑫的工程师来自世界各地，他们对技术充满热情，坚持不懈地致力于前沿低功耗 Wi-Fi+蓝牙双模物联网解决方案的研发。经过多年来在无线计算技术领域的深耕，我们开发出了绿色、用途广泛、高性价比的芯片组，提供安全、稳定可靠、低功耗的物联网解决方案，致力于实现我们一直以来恪守的使命：用技术共享推动万物智联。
## 1.3 原理简介
        根据红外线易被黑色电工胶带吸收的原理，我们使用黑色电工胶带制作行走路线，四个TR5000红外感应模块来获取路线信息。
        动力部分使用四节七号电池（共计6V）作为供电，驱动模块采用L298N模块驱动两路马达，采用基于乐鑫ESP8266模块的NodeMcu with Arduino处理获取到的信息并实时做出调控实现避障效果。

------

# 2. 开始制作
## 2.1 我们所需要的
    四节七号电池盒 x 1
    七号电池 x 4
    L298N驱动模块 x 1
    NodeMcu开发板 x 1
    减速马达 x 4
    亚克力底盘 x 2
    五金材料若干
## 2.2代码编写
        在准备好所需材料后，我们需要向单片机烧写程序。以下为代码节选，完整版见附录1。
### 2.2.1代码节选


```cpp
#include "MotorControl.h"
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
    A.initialize();
    B.initialize();
    Serial.println("setup ok");
}
```
```cpp
/*该头文件定义了有关减速电机驱动的函数*/
const int FORWARD[] ={0,1};
const int BACKWARD[]={1,0};
const int STOP[]    ={0,0};
class motor
{
    public:
        int com[2];
        int port[2];
        int power = 100;
        int EN;
        void initialize(void)
        {
            pinMode(port[0],OUTPUT);
            pinMode(port[1],OUTPUT);
            pinMode(EN,OUTPUT);
            Serial.println("Initlazed");
        }
        void run(void)
        {
            digitalWrite(port[0],com[0]);
            digitalWrite(port[1],com[1]);
            digitalWrite(EN,HIGH);
            Serial.println("running");
            if (power != 100)
            {
                Serial.println("running with PWM");
                delay(10 * power);
                digitalWrite(EN,LOW);
            }
        }
};
```
### 2.2.2 思路简介
        TCRT5000 传感器的红外发射二极管不断发射红外线，当发射出的红外线没有被反射回来或被反射回来但强度不够大时，红外接收管一直处于关断状态，此时模块的输出端为高电平，指示二极管一直处于熄灭状态；
        被检测物体出现在检测范围内时，红外线被反射回来且强度足够大，红外接收管饱和，此时模块的输出端为低电平，指示二极管被点亮

  MCU检测四个模块的电平信号，通常会有如下结果：
|信号1|信号2|信号3|信号4|操作|
|--|--|--|--|--|
|0|1|1|0|前进|
|0|0|1|1|右转|
|1|1|0|0|左转|
|0|0|0|0|停止|

  在一个周期中，MCU获得传感器信号，根据上表做出处理，并对马达做出相应操作，实现避障效果。
## 2.3安装
  如图示连接元器件
![](https://github.com/ShooterH/8266-autoCar/raw/main/img/layout.jpg)



# 3.总结

见"天长中学研究性学习课题总结"。


# 附录
1. 源代码
```cpp
/*该代码编写了小车运行的主要逻辑*/
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
    A.initialize();
    B.initialize();
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
```
```cpp
/*该头文件为电机驱动相关函数定义以及引脚定义*/
const int FORWARD[] ={0,1};
const int BACKWARD[]={1,0};
const int STOP[]    ={0,0};
class motor
{
    public:
        int com[2];
        int port[2];
        int power = 100;
        int EN;
        void initialize(void)
        {
            pinMode(port[0],OUTPUT);
            pinMode(port[1],OUTPUT);
            pinMode(EN,OUTPUT);
            Serial.println("Initlazed");
        }
        void run(void)
        {
            digitalWrite(port[0],com[0]);
            digitalWrite(port[1],com[1]);
            digitalWrite(EN,HIGH);
            Serial.println("running");
            if (power != 100)
            {
                Serial.println("running with PWM");
                delay(10 * power);
                digitalWrite(EN,LOW);
            }
        }
};

/*引脚定义
  在这里设置你的引脚*/
const int IN1  = 16;//D0
const int IN2  = 5; //D1
const int IN3  = 4;
const int IN4  = 0;
const int ENA  = 14; //D5
const int ENB  = 12; //D6

void comWr(const int status[2],int Power,motor &Motor)
{
    /*status为命令类型，包含前进，后退，制动*/
    /*power为电机调速变量，原理为PWM脉冲，输入范围为1-100（满速）*/
    /*Motor为要操控的电机，分别对应AB马达，输入变量ENA或ENB*/

    /*状态写入*/
    Motor.com[0] = status[0];
    Motor.com[1] = status[1];
    digitalWrite(Motor.port[0],status[0]);
    digitalWrite(Motor.port[1],status[1]);
    Motor.power = Power;
}
```
```cpp
/*该代码定义了循迹信号处理函数*/
const int S1 = 13;
const int S2 = 15;
const int S3 = 3;
const int S4 = 1;

void sensorInitialize(void)
{
    pinMode(S1,INPUT);
    pinMode(S2,INPUT);  
    pinMode(S3,INPUT);
    pinMode(S4,INPUT);
}

int *scan(void)
{
    int status[4];
    status[0] = digitalRead(S1);
    status[1] = digitalRead(S2);
    status[2] = digitalRead(S3);
    status[3] = digitalRead(S4);
    return status;
}
```