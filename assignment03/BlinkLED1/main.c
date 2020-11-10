#define RCC_BASE 0x40021000
#define RCC_AHB2ENR (*((unsigned int*)(RCC_BASE + 0x4C)))

#define GPIOA_BASE 0x48000000
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR   (*((unsigned int*)(GPIOA_BASE + 0x14)))

#define ODR5 (1 << 5)

volatile int counter = 0;

int main()
{
    // RCC Base Address: 0x40021000
    // RCC AHB2 Peripheral clock enable register (RCC_AHB2ENR)
    // Address Offset: 0x4C
    // Set bit[0]/ GPIOAEN to 1
    // Enable clock to GPIO peripheral
    RCC_AHB2ENR |= 0x1;
    
    // GPIOB Base Address: 0x48000400
    // GPIO port mode register (GPIOB_MODER)
    // Address Offset: 0x00
    // Set bit[29:28] to 0x1 -> to enable PB14 as output
    GPIOA_MODER &= 0xFFFFF7FF; //0xABFFF7FF
    
    // GPIOB Base Address: 0x48000400
    // GPIO port output data register (GPIOB_ODR)
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
        
        GPIOA_ODR |= ODR5;
        counter = 0;
        while (counter < 100000)
        {
            counter++;
        }
        
        GPIOA_ODR &= ~ODR5;
        
    }
    
}
