#include <stdint.h>
#include <avr/io.h>
#include <Arduino.h>
#ifndef PULSE_H
#define PULSE_H

#include <Timer.h>


class Pulse 
{   
    public:
        Pulse();
        void attach(int8_t PWMpin);
        void setRate(int8_t rate);
        void update(bool pulseEnable);
        void setMax(int8_t maxVal);
        void setMin(int8_t minVal);
        void setIncrement(int8_t increment);
    private:
        int8_t PWMpin;
        bool pulseEnable;
        int8_t rate;
        int8_t maxVal = 255; //max value to raise light to
        int8_t minVal = 0; //min value to lower light to
        int8_t increment = 5; //how many increments to increase
        bool En = 0; //bool to hold direction of pulse
        MoToTimer lightRaise; // Declare lightRaise as a member variable
        MoToTimer lightLower; // Declare lightLower as a member variable

};



#endif