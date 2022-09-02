#include <stdio.h>

int v[101];
int fibonacci(int n)
{
    if(n<=1)
        return 1;
    int f1,f2;
    if(v[n-1]==0)
        f1=fibonacci(n-1);
    else
        f1=v[n-1];
    if(v[n-2]==0)
        f2=fibonacci(n-2);
    else
        f2=v[n-2];
    v[n]=f1+f2;
    return f1+f2;
}

int main()
{
    int k;
    scanf("%d",&k);
    printf("%d ",fibonacci(k));
    return 0;
}