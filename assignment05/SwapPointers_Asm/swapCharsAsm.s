/*******************************************************************************
File name       : swapCharsAsm.s
Description     : Assembly language function for divsion by two
*******************************************************************************/   
    
    PUBLIC swapCharsAsm       // Exports symbols to other modules
                                // Making swapCharsAsm available to other modules.
    
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
Function Name   : swapCharsAsm
Description     : computes the division by two of its input argument
C Prototype     : int swapCharsAsm(char *val1, char* val2)
                : Where val1 & val2 are pointers to variables to swap
Parameters      : R0, R1: char val
Return value    : R0
*******************************************************************************/  
  
swapCharsAsm
    //PUSH {R4,LR}        // save the R4 local variable value and return address
    //Swapping values
    LDRB R2,[R0]        // load R0 byte content into R2 temp register
    LDRB R3,[R1]        // load R1 byte content into R3 temp register
    STRB R3,[R0]        // store R3 value into [R0] location
    STRB R2,[R1]        // store R2 value into [R1] location
    // Compare values
    MOVS R0, R2         // Move content of R2 to R0 - R0 will be used to conduct compare and return result
    CMP  R0, R3          // compare values at location [R0] & [R1]
    BNE.N RETURN1
    MOVS R0, #0
    BNE.N RETURN0
    RETURN1:
        MOVS R0, #1
        RETURN0:
            //POP {R4,LR}         // Restore R0 and LR
            BX LR               // return (with function result in R0)
    END
