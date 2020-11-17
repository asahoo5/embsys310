
int func1 (int var0, int var1, int var2, int var3, int var4);

int main()
{
    int result = 0;
    result = func1(1,2,3,4,5);
    return result;
}

int func1 (int var0, int var1, int var2, int var3, int var4)
{
    int lvar0 = var0;
    int lvar1 = var1;
    int lvar2 = var2;
    int lvar3 = var3;
    int lvar4 = var4;
    
    int sum;
    
    sum = lvar0 + lvar1 +lvar2 +lvar3 + lvar4;
    
    return sum;
}
