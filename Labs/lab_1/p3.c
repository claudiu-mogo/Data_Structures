#include <stdio.h>

int fibonacci(int k,int n, int crt1, int crt2)
{
    if(n==k)
        return crt2;
    return fibonacci(k,n+1,crt2,crt1+crt2);
}

int fibonacci2(int k)
{
    if(k==0||k==1)
        return 1;
    return fibonacci2(k-1)+fibonacci2(k-2);
}

int main()
{
    int k;
    scanf("%d",&k);
    printf("%d ",fibonacci(k,0,0,1));
    printf("%d",fibonacci2(k));
    return 0;
}