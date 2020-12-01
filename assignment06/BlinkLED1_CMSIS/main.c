#include "stm32l475xx.h"
#include "system_stm32l4xx.h"

volatile int counter = 0;

int main()
{
    // RCC Base Address: 0x40021000
    // RCC AHB2 Peripheral clock enable register (RCC->AHB2ENR)
    // Address Offset: 0x4C
    // Set bit[0]/ GPIOAEN to 1
    // Enable clock to GPIO peripheral
    
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // GPIOA Base Address: 0x48000000
    // GPIO port mode register (GPIOA->MODER)
    // Address Offset: 0x00
    // Set bit[11:10] to 0x1 -> to enable PB5 as output
    
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    
    // GPIOA Base Address: 0x48000000
    // GPIO port output data register (GPIOA->ODR)
    // Address Offset: 0x14
    // Set bit[5] to 0x1 -> 0x4000; // Turn LED ON
    // Set bit[5] to 0x0 -> 0x0;    // Turn LED OFF
    // This will get LED1 blinking
    
    while (1)
    {
        counter = 0;
        while (counter < 100000)
        {
            counter++;
        }
        
        GPIOA->ODR |= GPIO_ODR_OD5;
		
        counter = 0;
        while (counter < 100000)
        {
            counter++;
        }
        
        GPIOA->ODR &= ~GPIO_ODR_OD5;
    }
    
}

