#include <stdio.h>
#define NMAX 101

int aux[NMAX];

void mergesort(int v[],int st,int dr)
{
    int mij=(st+dr)/2;
    if(st>=dr)
        return ;
    mergesort(v,st,mij);
    mergesort(v,mij+1,dr);
    int i=st,j=mij+1,k=0;
    while(i<=mij&&j<=dr)
    {
        if(v[i]<v[j])
        {
            aux[k++]=v[i++];
        }
        else
            aux[k++]=v[j++];
    }
    while(i<=mij)
        aux[k++]=v[i++];
    while(j<=dr)
        aux[k++]=v[j++];
    for(i=0;i<k;i++)
        v[st+i]=aux[i];
}

int main()
{
    int v[101],i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&v[i]);
    mergesort(v,0,n-1);
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    return 0;
}