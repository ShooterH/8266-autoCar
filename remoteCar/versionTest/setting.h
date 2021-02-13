#ifndef SETTING_H_
#define SETTING_H_
#endif

const int MOTORL = 0;
const int MOTORR = 1;
const int EnableA = 2;
const int EnableB = 3;
class motor
{
    public:
        int port[2];
        int com[2];
        int power = 100;
        int EN;
        void comWr(void)
        {
            digitalWrite(port[0],com[0]);
            digitalWrite(port[1],com[1]);
        }
};

const int FORWARD[] ={0,1};
const int BACKWARD[]={1,0};
const int STOP[]    ={0,0};
