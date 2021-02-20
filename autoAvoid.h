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