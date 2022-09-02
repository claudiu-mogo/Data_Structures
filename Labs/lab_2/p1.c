#include <stdio.h>

int fibonacci(int k,int n, int f1, int f2)
{
    if(n==k)
        return f2;
    return fibonacci(k,n+1,f2,f1+f2);
}

int main()
{
    int k;
    scanf("%d",&k);
    printf("%d ",fibonacci(k,0,1,1));
    return 0;
}