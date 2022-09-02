#include <stdio.h>
#include <math.h>

double radical(int n,double start,double fin)
{
    double mij=(start+fin)/2;
    if(fabs(n-mij*mij)<=0.001)
        return mij;
    if(mij*mij<n)
    {
        return radical(n, mij+0.001,fin);
    }
    if(mij*mij>n)
        return radical(n,start,mij-0.001);
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%0.3lf ",radical(n,0,n));
    return 0;
}