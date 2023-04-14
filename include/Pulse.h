#ifndef PULSE_H
#define PULSE_H

class Pulse 
{   
    public:
        Pulse();
        void attach(int PWMpin);
        void setRate(int rate);
        void update(bool pulseEnable);
        void setMax(int maxVal);
        void setMin(int minVal);
    private:
        int PWMpin;
        bool pulseEnable;
        int rate;
        int maxVal = 255; //max value to raise light to
        int minVal = 0; //min value to lower light to
        int increment = 5; //how many increments to increase
        bool En = 0; //bool to hold direction of pulse

};



#endif