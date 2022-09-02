#include <stdio.h>
#include <string.h>

int palindrom(char *s,int init, int fin)
{
    if(init>=fin)
        return 1;
    if(s[init]!=s[fin])
        return 0;
    return palindrom(s,init+1,fin-1);
}

int main()
{
    char s[101];
    gets(s);
    printf("%d",palindrom(s,0,strlen(s)-1));
    return 0;
}