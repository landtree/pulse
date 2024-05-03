/*
This uses the GPL-3.0 Licence.

It uses the MoToTimer from the MoBaTool library for timing.
https://github.com/MicroBahner/MobaTools

***Using the modified OMSI Timer that is a stripped down version of Mobatools*****


*/


#include <Pulse.h>

Pulse::Pulse()
{
    // Create a new MoToTimer object for light raising
    lightRaise = MoToTimer();
    lightLower = MoToTimer();
}

void Pulse::attach(int8_t PWMpin)
{   
    Pulse::PWMpin = PWMpin; 
 
}

void Pulse::setRate(int8_t rate)
{
    Pulse::rate = rate;
}

void Pulse::setMax(int8_t maxVal)
{
    Pulse::maxVal = maxVal;
}

void Pulse::setMin(int8_t minVal)
{
    Pulse::minVal = minVal;
}

void Pulse::setIncrement(int8_t increment)
{
    Pulse::increment = increment;
}


void Pulse::update(bool pulseEnable)
{
        if(lightRaise.running() == false)
        {   
            if(pulseEnable == 1)
            {
                //En 0 == raise light
                if(En == 0)
                {   
                    increment++;
                    analogWrite(PWMpin, increment);
                    lightRaise.setTime(rate);                    
                    if(increment == maxVal){En = 1;}      
                }
            
                //EN 1 == lower light
                if(En == 1)
                {  
                    increment--; 
                    analogWrite(PWMpin, increment);
                    lightRaise.setTime(rate);
                    if(increment == minVal){En = 0;}            
                }
            }
        }
        if(lightLower.running() == false)
        {
            //fade out when game start
            if(pulseEnable == 0)
            {   
                if(increment > 0)
                {
                increment--; 
                analogWrite(PWMpin, increment);
                lightLower.setTime(rate);
                lightLower.restart();
                }
                if(increment == 0){En = 0;}    
            }
        }


}