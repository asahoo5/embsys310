#include "delay.h"
#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

#define SYS_CLOCK_HZ 4000000u   // Default clock after startup
#define TICK_RATE_HZ 1000u      // 1 KHz = 1 ms tick

void SysTick_Initialize(void);

uint32_t uTickCounter = 0u;    // GLobal Tick counter variable, increments every 1 ms

void main(void)
{
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    // RCC Base Address: 0x40021000
    // Address offset: 0x4C
    // Set bit[1] to 1
    // 1. Enable clock to Peripheral  
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x00
    // Set bit[11:10] to 0x01  so --> 0x400 // To enable PB5 as output
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    
    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // GPIOA Base Address: 0x48000000
    // Address offset: 0x5
    // Set bit[5] to 1 --> 0x20;   // Turn LED ON
    // Set bit[5] to 0 --> 0x0;    // Turn LED OFF
    
    SysTick_Initialize();

    while(1)
    {
        GPIOA->ODR ^= GPIO_ODR_OD5;
        delay(5000);              //delay of 5 second
    }    
}

void SysTick_Initialize(void)
{
    /* 
     *   Load the counter timer value to trigger SYSTick timer interrupt on every 1ms 
     *   With Clock @4MHz, system clock ticks every (1/4MHz) = 0.25 us
     *   Once counter value loaded, it decrements on every system clock tick.
     *   Hence in order to trigger interrupt every 1 ms (TICK), load value = 
     *   (1 ms / 0.25 us) - 1 = (4000000 / 1000) - 1  = 3999.
     */
    SysTick->LOAD = (SYS_CLOCK_HZ / TICK_RATE_HZ) - 1;       // 0xE000E014 - Counts down to 0.
    SysTick->VAL = 0x0;                                      // 0xE000E018 - Clears initial value
    SysTick->CTRL = 0x7;                                     // 0xE000E010 - Enable interrupts
}

void SysTick_Handler(void)
{
    __disable_irq();
    ++uTickCounter;
    __enable_irq();
}
