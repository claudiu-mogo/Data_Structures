#include <stdio.h>

int cautare_binara(int start,int fin,int v[],int x)
{
    if(fin>=start)
    {
        int mij=(start+fin)/2;
        if(v[mij]==x)
            return mij;
        if(v[mij]>x)
            return cautare_binara(start,mij-1,v,x);
        if(v[mij]<x)
            return cautare_binara(mij+1,fin,v,x);
    }
    return -1;
}

int cautare_rotit(int v[],int n,int x)
{
    //rotire
    int i=0,aux1[100],aux2[100],k1=0,k2=0;
    while(v[i]<v[i+1]&&i<n)
        i++;
    int shift=i;
    for(++i;i<n;i++)
        aux1[k1++]=v[i];
    for(i=0;i<=shift;i++)
        aux2[k2++]=v[i];
    for(i=0;i<k1;i++)
        v[i]=aux1[i];
    for(i=0;i<k2;i++)
        v[k1+i]=aux2[i];
        /*
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
    */
    //cautare binara
    int rez=cautare_binara(0,n-1,v,x);
    if(rez==-1)
        return -1;
    if(rez<n-shift-1)
        return rez+shift+1;
    return rez+shift-n+1;
}

int main()
{
    int n,v[101],i,x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&v[i]);
    scanf("%d",&x);
    x=cautare_rotit(v,n,x);
    if(x==-1)
        printf("Nu exista");
    else
        printf("%d",x);
    return 0;
}