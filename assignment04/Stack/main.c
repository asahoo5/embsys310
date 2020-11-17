#include<assert.h>
#include"stack.h"

int main()
{
    int result1;
    int result2;
    int testItem;
    
    // *******************************************************************
    // Test1: Retrieve item from an empty stack
    // *******************************************************************
    // Arrange:
    result1 = 42;
    testItem = 1;
    stack_init();
    
    // Act:
    result1 = stack_pop(&testItem);
      
    // Assert:
    assert(-1 == result1);
    assert(1 == is_stack_empty());
    assert(1 == testItem);
    
   
    // *******************************************************************
    // Test2: Successfully retrieve an item from the stack
    // *******************************************************************
    // Arrange:
    result1 = 42;
    result2 = 42;
    testItem = 10;
    stack_init();
    
    // Act:
    result1 = stack_push(10);
    result2 = stack_pop(&testItem);
    
    // Assert:
    assert(0 == result1);
    assert(0 == result2);
    assert(10 == testItem);
    
   
    // *******************************************************************
    // Test3: Fill stack, then get all items.
    // *******************************************************************
    // Arrange:
    testItem = 1;
    stack_init();
    
    // Act:
    stack_push(2);
    stack_push(3);
    stack_push(4);                                    
    
    // Assert:
    assert(1 == is_stack_full());
    
    assert(0 == stack_pop(&testItem));
    assert(4 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(3 == testItem);
    
    assert(0 == stack_pop(&testItem));
    assert(2 == testItem);
    
    assert(1 == is_stack_empty());

    
      
    // *******************************************************************
    // Test4: Fill stack, then put one more item, should fail
    // *******************************************************************
    // Arrange:
    testItem = 1;
    stack_init();
    
    // Act:
    stack_push(2);
    stack_push(3);
    stack_push(4);
    
    // Assert:
    assert(-1 == stack_push(5));

    assert(0 == stack_pop(&testItem));
    assert(4 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(3 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(2 == testItem);



    // ***********************************************************************
    // Test5: Fill stack, retrieve one item, then add item, then retieve all
    // ***********************************************************************
    // Arrange:
    testItem = 1;
    stack_init();
    
    // Act:
    stack_push(2);
    stack_push(3);
    stack_push(4);
    
    // Assert:
    assert(0 == stack_pop(&testItem));
    assert(4 == testItem);

    assert(0 == stack_push(5));
    
    assert(1 == is_stack_full());

    assert(0 == stack_pop(&testItem));
    assert(5 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(3 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(2 == testItem);


    // ***************************************************************************************************************************************
    // Test6: Fill stack and retrieve all items. Do it twice in a row. Test Is Empty() and Is Full() in when not empty & not full respectively
    // ***************************************************************************************************************************************
    // Arrange:
    testItem = 1;
    stack_init();
    
    // Act:
    stack_push(2);
    stack_push(3);
    stack_push(4);
    
    // Assert:
    assert(0 == stack_pop(&testItem));
    assert(4 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(3 == testItem);

    assert(-1 == is_stack_full());
    assert(-1 == is_stack_empty());
    
    assert(0 == stack_pop(&testItem));
    assert(2 == testItem);

    assert(0 == stack_push(5));
    assert(0 == stack_push(6));
    assert(0 == stack_push(7));
        
    assert(1 == is_stack_full());

        
    assert(-1 == stack_push(8));

    assert(0 == stack_pop(&testItem));
    assert(7 == testItem);
   
    assert(0 == stack_pop(&testItem));
    assert(6 == testItem);

    assert(0 == stack_pop(&testItem));
    assert(5 == testItem);
    
    assert(-1 == stack_pop(&testItem));
    
    assert(1 == is_stack_empty());

    return 0;
}
