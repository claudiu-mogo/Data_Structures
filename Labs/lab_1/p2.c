#include <stdio.h>

int sum(int v[], int n)
{
    if(n==0)
        return 0;
    return v[n-1]+sum(v,n-1);
}

int main()
{
    int v[101],n,x,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&v[i]);
    printf("%d",sum(v,n));  
    return 0;
}