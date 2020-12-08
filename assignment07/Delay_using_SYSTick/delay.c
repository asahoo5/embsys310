#include "delay.h"

void delay(unsigned int delay_in_milliseconds)
{
    unsigned int tickstart = uTickCounter;
    
    unsigned int delay = delay_in_milliseconds;
    
    while ((uTickCounter - tickstart) < delay)
    {   
    }
}