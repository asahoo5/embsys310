#include "stm32l475xx.h"
#include "system_stm32l4xx.h"

#define ON  1
#define OFF 0

#define GPIOA_CLK_EN_BIT 0

void enable_rcc(int bit_position);
void delay(uint32_t counter);
void control_user_led1(uint32_t state, uint32_t delay_counter);

int main()
{
    // Enable clock to GPIO peripheral using assembly code - that uses bitbanding address
    enable_rcc(GPIOA_CLK_EN_BIT);
    
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
    // This will get LED1 blinking - Use control_user_led1() alternatively
    
    while (1)
    {
        
        /*delay(100000);
        
        GPIOA->ODR |= GPIO_ODR_OD5;
        
        delay(100000);
        
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        */
        
        control_user_led1(ON, 100000);
        control_user_led1(OFF, 100000);
    }
    
}
