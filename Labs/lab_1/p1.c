#include <stdio.h>

int count(int v[], int n,int x)
{
    if(!n)
        return 0;
    if(v[n-1]==x)
        return 1+count(v,n-1,x);
    else
        return count(v,n-1,x);
}

int main()
{
    int v[101],n,x,i;
    scanf("%d%d",&n,&x);
    for(i=0;i<n;i++)
        scanf("%d",&v[i]);
    printf("%d",count(v,n,x));
    return 0;
}