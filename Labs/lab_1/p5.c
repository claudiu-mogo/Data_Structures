#include <stdio.h>

int putere(int a,int n)
{
    if(n==0)
        return 1;
    if(n==1)
        return a;
    int k=putere(a,n/2);
    if(n%2)
        return a*k*k;
    else
        return k*k;
}

int main()
{
    int a,n;
    scanf("%d%d",&a,&n);
    printf("%d",putere(a,n));
    return 0;
}