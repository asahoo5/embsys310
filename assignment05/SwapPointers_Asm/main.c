int swapCharsAsm(char* x, char* y);
int swapPointersAsm(char *x, char *y);

int main()
{
    char x = '1', y = '2';
    if(swapCharsAsm(&x, &y) == swapPointersAsm(&x, &y))
        return 0; // Assembly worked successfully; Verify x & y holds same value as assigned
    else
        return 1; // Revisit assembly code
}

/*
 * Swapping 
*/
int swapPointersAsm(char *x, char *y)
{    
    char tempPtr = *x;
    *x = *y;
    *y = tempPtr;
    if(*x == *y)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}