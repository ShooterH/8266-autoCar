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
            Serial.println("Initialized");
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
