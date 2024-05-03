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
    setupPWM();   
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


void writePWM(uint8_t pin, uint8_t value) {
    // Map value (0-255) to PWM duty cycle (0-65535)
    uint16_t dutyCycle = (uint16_t)value * 256;

    // Select the appropriate timer and output compare register based on the pin
    switch (pin) {
        case 0: // Example pin, replace with the actual pin number on your ItsyBitsy
            // Configure Timer0 for Fast PWM mode, non-inverting
            TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
            TCCR0B |= (1 << CS00); // No prescaling
            OCR0A = dutyCycle;
            break;
        // Add cases for other pins as needed
        default:
            // Unsupported pin
            break;
    }
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
                    writePWM(PWMpin, increment);
                    lightRaise.setTime(rate);                    
                    if(increment == maxVal){En = 1;}      
                }
            
                //EN 1 == lower light
                if(En == 1)
                {  
                    increment--; 
                    writePWM(PWMpin, increment);
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
                writePWM(PWMpin, increment);
                lightLower.setTime(rate);
                lightLower.restart();
                }
                if(increment == 0){En = 0;}    
            }
        }


}