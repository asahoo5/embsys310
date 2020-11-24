void swap(int* x, int* y);
void swap_pointer(int** x, int** y);

int main()
{
    int x = 100, y = 200;
    int *xPtr = &x;
    int *yPtr = &y;
    //swap(&x, &y);
    //swap(xPtr, yPtr);
    swap_pointer(&xPtr, &yPtr);
    return 0;
}


/*
 * Swapping by pass by pointer variables
*/
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    
    //Swapping of pointers - swaps the local variables (similar to pass by variables), not the expected passed in pointers xPtr & yPtr
    /*
    int *tempPtr = x;
    x = y;
    y = tempPtr;
    */
}

/*
 * Swapping of pointers by pass by pointer variables
 * Swapping of pointers - this swaps pointer variables, not the values they hold.
 * (**) gives it a way to refer to pointer variables, so it can change them. 
*/
void swap_pointer(int** x, int** y)
{    
    //Swapping of pointers
    int *tempPtr = *x;
    *x = *y;
    *y = tempPtr;
}