#include <stdio.h>
#include <math.h>

int maxim(int a,int b)
{
    if(a>=b)
        return a;
    return b;
}

int nr_digits(int x)
{
    int count=0;
    do {
        x /= 10;
        ++count;
    } while (x != 0);
    return count;
}

int produs(int a,int b,int n1,int n2)
{
    if(b<10)
        return a*b;
    int a1,a2,b1,b2,n;
    n=maxim(n1,n2);
    a1=a/(int)(pow(10,n/2));
    a2=a%(int)(pow(10,n/2));
    b1=b/(int)(pow(10,n/2));
    b2=b%(int)(pow(10,n/2));
    printf("%d %d %d %d\n",a1,a2,b1,b2);
    int p=produs(a1,b1,nr_digits(a1),nr_digits(b1));
    printf("%d\n",p);
    int q=produs(a2,b2,nr_digits(a2),nr_digits(b2));
    printf("%d\n",q);
    int sum1=a1+a2,count1=0,sum2=b1+b2,count2=0;
    count1=nr_digits(sum1);
    count2=nr_digits(sum2);
    int r=produs(a1+a2,b1+b2,nr_digits(sum1),nr_digits(sum2));
    printf("%d\n",r);
    return (int)(pow(10,(n/2)*2))*p + (int)(pow(10,n/2))*(r-p-q) + q;
}

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",produs(a,b,nr_digits(a),nr_digits(b)));
    return 0;
}