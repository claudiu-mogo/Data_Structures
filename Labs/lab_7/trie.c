#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int count, nrfii;
    struct Trie* child[26];
}Trie;

void init(Trie **t)
{
    *t=malloc(sizeof(Trie));
    (*t)->count=(*t)->nrfii=0;
    for(int i=0;i<26;i++)
        (*t)->child[i]=NULL;
}

void insert(Trie *t,char *sir)
{
    //daca s-a terminat cuvantul
    if(sir[0]=='\n')
    {
        t->count++;
        return;
    }
    //cream nodul corespunzator
    int valoare_litera=sir[0]-'a';
    //printf("%c\n",valoare_litera+'a');
    if(t->child[valoare_litera]==NULL)
    {
        init(&(t->child[valoare_litera]));
        t->nrfii++;
    }
    insert(t->child[valoare_litera],sir+1);
}

int delete_trie(Trie *t, char *sir)
{
    int valoare_litera=sir[0]-'a';
    //daca ajungem la finalul cuvantului, facem ca si cum nu ar mai exista
    if(sir[0]=='\n')
    {
        t->count--;
    }
    else
    {
        //cautam prin trie pana ajungem la null si la intoarcere stergem nodul
        //nu vrem sa stergem noduri care intra in componenta altor cuv
        if(delete_trie(t->child[valoare_litera],sir+1))
        {
            t->child[valoare_litera]=NULL;
            t->nrfii--;
        }
    }
    if(t->count==0&&t->nrfii==0)
    {
        free(t);
        //adica se poate sterge si recursiv
        return 1;
    }
    //adica nu se poate sterge
    return 0;
}

void free_trie(Trie **t)
{
    if((*t)!=NULL)
    {
        for(int i=0;i<26;i++)
            free_trie(&((*t)->child[i]));
        free((*t));
    }
}

//cautam cate cuvinte exista de la un moment dat pana la final
int cautare_cuvinte(Trie *t)
{
    if(t!=NULL)
    {
        int s=0;
        for(int i=0;i<26;i++)
        {
            s+=cautare_cuvinte(t->child[i]);
        }
        return s+t->count;
    }
    return 0;
}

int cautare_cuvant(Trie *t, char *sir)
{
    if(sir[0]=='\n')
    {
        //-1 ca sa nu se puna si pe sine
        return cautare_cuvinte(t)-1;
    }
    int valoare_litera=sir[0]-'a';
    if(t->child[valoare_litera]!=NULL)
    {
        return cautare_cuvant(t->child[valoare_litera],sir+1);
    }
    //daca nu e nici final, nici nu am gasit litera
    return 0;
}

int main()
{
    int n,k,i,j;
    char kwvint[256],allwords[20][256];
    Trie *t;
    init(&t);
    FILE *f1,*f2;
    f1=fopen("lab7.in","r");
    f2=fopen("lab7.out","w");
    fscanf(f1,"%d%d",&n,&k);
    fgetc(f1);
    for(i=0;i<n;i++)
    {
        fgets(kwvint,256,f1);
        printf("%s",kwvint);
        insert(t,kwvint);
        strcpy(allwords[i],kwvint);
    }
    for(i=0;i<n;i++)
    {
        for(j=1;j<=k;j++)
        {
            //printf("%s",allwords[i]);
            strncpy(kwvint,allwords[i],j);
            kwvint[j]='\n';
            kwvint[j+1]='\0';
            printf("%s",kwvint);
            fprintf(f2,"%d ",cautare_cuvant(t,kwvint));
        }
        fprintf(f2,"\n");
    }
    free_trie(&t);
    fclose(f1); fclose(f2);
    return 0;
}