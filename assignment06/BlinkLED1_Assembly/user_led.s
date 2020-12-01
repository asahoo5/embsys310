/*******************************************************************************
File name       : user_led.s
Description     : Assembly language function for controlling the user LED
*******************************************************************************/   

    EXTERN delay                    // delay() is defined outside this file

    PUBLIC control_user_led1        // Exports symbols to other modules

// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables. The syntax for declaring bss section is -
//      The text section is used for keeping the actual code.

// CODE: Interprets subsequent instructions as Arm or Thumb instructions, 
// depending on the setting of related assembler options.

// NOREORDER (the default mode) starts a new fragment in the section
// with the given name, or a new section if no such section exists.
// REORDER starts a new section with the given name.

// NOROOT means that the section fragment is discarded by the linker if
// no symbols in this section fragment are referred to. Normally, all
// section fragments except startup code and interrupt vectors should
// set this flag.

// The (2) is for the (align)
// The power of two to which the address should be aligned.
// The permitted range is 0 to 8. 
// Code aligned at 4 Bytes.

    SECTION .text:CODE:REORDER:NOROOT(2)
    
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions
    
/*******************************************************************************
Function Name   : control_user_led1
Description     : - Uses Peripheral registers at base 0x4800.0000
                    to set GPIOA Output Data Register.
                  - Calls another assembly function delay to insert
                    delay loop

C Prototype     : void control_user_led(uint8_t state, uint32_t duration)
                : Where state indicates if LED should be on or off.
Parameters      : R0: uint8_t state
                : R1: uint32_t duration
Return value    : None
*******************************************************************************/  

GPIOA_BASE  EQU 0x48000000
GPIOA_ODR   EQU 0x14
GPIOA_BIT_5 EQU 0x20

control_user_led1
    // <TODO> Implement function in assembly
    PUSH {R4, LR}        // Push R4, LR to stack, to be extracted to return to main function
    LDR R2, =GPIOA_BASE  // Store GPIOA_BASE gloabal variable to R2
    LDR R3, =GPIOA_ODR   // Store GPIOA_ODR gloabal variable to R3
    ADDS R2, R2, R3      // Calculare the address of the GPIO Output data Register
    LDR R4, [R2]         // Obtain content of GPIO Output data Register
    LDR R3, =GPIOA_BIT_5 // Store GPIOA_BIT_5 gloabal variable to R3
    CMP R0, #0           // Compare to see if user called for ON (1) or OFF (0) state
    BEQ RESET            // Branch to RESET if OFF state is called
    ORRS.W R4, R4, R3    // OR'd the GPIO Output data Register value to set the it's Bit 5 data
    B.N STORE
    RESET: 
         BICS.W R4, R4, R3 // GPIO Output data Register's Bit 5 data is reset
         B.N STORE
    STORE:
         STR R4, [R2]      // Store in physical location 0x48000014
    MOV R0, R1             // Move R1 to R0 to pass argument to delay()
    BL delay               // Call to delay()
    POP {R4, LR}           // Pop R4 and LR
    BX LR                  // Branch to main function
    END
