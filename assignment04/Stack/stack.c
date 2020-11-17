#include "stack.h"
#define STACK_SIZE 3

// Backing store
int StackStore[STACK_SIZE]; //stack grows upwards

// Pointer to stack elements for adding and retrieving
int* topPtr;

// FIFO Queue is Empty if putPtr==getPtr;
// FIFO Queue is Full if putPtr+1 > Address of last element in the stack;

// Initialize internals of the stack
void stack_init(void)
{
    topPtr = 0;
    for(int i=0; i<STACK_SIZE; i++)
    {
        StackStore[i] = 0;
    }
}

// Add data to stack
// If stack is full return error
// Otherwise return success
// Note function could be void since we have is_stack_full() & is_stack_empty()
int stack_push(int data)
{
    if (topPtr == &StackStore[STACK_SIZE - 1])
    {
        // stack is full
        return -1;
    }     
    
    if (topPtr == 0)
    {
        topPtr = &StackStore[0];
    }
    else
    {
        topPtr++;
    }
    
    *topPtr = data;
    return 0;
}

// Get data from stack
// If stack is empty return error
// Otherwise return success
// Note function could be void since we have is_stack_full() & is_stack_empty()
int stack_pop(int* data)
{   
    if (topPtr == 0)
    {
        // stack is empty or never filled
        return -1;
    }

    *data = *topPtr;
    
    if(topPtr == &StackStore[0])
    {
        topPtr = 0;
    }
    else
    {
        topPtr--;
    }
    
    return 0;
}

int is_stack_full()
{
    return (topPtr == &StackStore[STACK_SIZE - 1]) ? 1 : -1;
}

int is_stack_empty()
{
    return (topPtr == 0) ? 1 : -1;
}
