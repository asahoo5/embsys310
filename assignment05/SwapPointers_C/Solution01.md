void swap_pointer(int** x, int** y);

main()
{
...
   swap_pointer(&xPtr, &yPtr);
...
}

a) Before calling function swap_pointer(), main fn stores the variables x , y, xPtr(points to x), yPtr(points to y) in the stack in the order they were assigned.
   Then main fn uses R0 & R1 register (Argument registers) to pass the references of xPtr & yPtr to the function, which accepts pointer of pointer variables.

b) R0 - 0x20001FEC i.e. memory location of xPtr
   R1 - 0x20001FE8 i.e. memory location of yPtr 

c) Attached local variable states screenshot to the SwapPointer folder.
