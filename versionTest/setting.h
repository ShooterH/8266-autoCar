#ifndef SETTING_H_
#define SETTING_H_
#endif

const int Rin1    = 5;//D5
const int Rin2    = 4;//D6
const int Lin1    = 0;//D7
const int Lin2    = 2;//D8
const int EnableA = 10;//D9
const int EnableB = 9;//D10M
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
