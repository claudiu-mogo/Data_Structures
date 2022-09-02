#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "treap.h"

// chiar functioneaza hashtableul. Afiseaza intai nr bucketului si apoi
// continutul listei respective

// trebuie compilat si cu -lm

typedef struct nod
{
    char *val;
    struct nod* next;
}nod;

typedef struct hashtable
{
    struct nod** Table; // vector de nod*, initial toate sunt NULL
    int nr_buckets;
    unsigned int (*hfunc) (char*);
    int size; // cate elemente avem in hashtable
}hashtable;

typedef struct treaptable
{
    struct Treap_node** Table; // vector de nod*, initial toate sunt NULL
    int nr_buckets;
    unsigned int (*hfunc) (char*);
    int size; // cate elemente avem in hashtable
}treaptable;

unsigned int hfunc(char *str)
{
    unsigned int sum=0,i;
    //puts(str);
    for(i=0;i<strlen(str);i++)
    {
        sum+=(((str[i]-'a'+1))*pow(26,i));
    }
    //printf("%d\n",strlen(str));
    return (sum%50);
}

// hashtable normal

void init_Hash(hashtable **h)
{
    int i;
    *h=(hashtable*)malloc(sizeof(hashtable));
    (*h)->nr_buckets=50;
    (*h)->hfunc=hfunc;
    (*h)->Table=(nod**)malloc(50*sizeof(nod*));
    for(i=0;i<50;i++)
    {
        (*h)->Table[i]=NULL;
    }
    (*h)->size=50; 
}

void insert(char *o,hashtable **h)
{
    unsigned int bucket=hfunc(o);
    //puts(o);
    //printf("%u\n",bucket);
    nod *n;
    n=(nod*)malloc(sizeof(nod));
    n->val=malloc((strlen(o)+1)*sizeof(char));
    strcpy(n->val,o);
    //n->val=o;
    n->next=(*h)->Table[bucket];
    (*h)->Table[bucket]=n;
}

int find(char *o, hashtable *h)
{
    unsigned int bucket=hfunc(o);
    //puts(o);
    //printf("%u\n",bucket);
    nod *n=h->Table[bucket];
    while(n!=NULL)
    {
        if(!strcmp(n->val,o))
        {
            return 1;
        }
        n=n->next;
    }
    return 0;
} 

void delete(char *o, hashtable *h)
{
    int bucket=hfunc(o);
    nod *n=h->Table[bucket];
    nod *p=n;
    if(p->next==NULL&&!strcmp(n->val,o))
    {
        free(p->val);
        free(p);
        h->Table[bucket]=NULL;
    }
    else
    {
        if(!strcmp(n->val,o))
        {
            n=n->next;
            free(p->val);
            free(p);
            return;
        }
        while(p->next!=NULL)
        {
            if(!strcmp(p->next->val,o))
            {
                nod *q=p->next;
                p->next=p->next->next;
                free(q->val);
                free(q);
                return;
            }
            p=p->next;
        }
    }
}

void print_list(nod *p,FILE* f2)
{
    while(p!=NULL)
    {
        fprintf(f2,"%s\n",p->val);
        p=p->next;
    }
}

void print_hashtable(hashtable *h,FILE* f2)
{
    int i;
    //printf("aici");
    for(i=0;i<50;i++)
    {
        if(h->Table[i]!=NULL)
        {
            fprintf(f2,"%u\n",i);
            print_list(h->Table[i],f2);
            //printf("\n");
        }
    }
}

void free_list(nod **node)
{
    nod *p=*node;
    while(p!=NULL)
    {
        nod *q=p;
        p=p->next;
        free(q);
    }
}

void free_hash(hashtable **h)
{
    for(int i=0;i<50;i++)
    {
        free_list(&(*h)->Table[i]);
    }
    free((*h)->Table);
    free(*h);
}

// pt treap

void init_Treaptable(treaptable **h)
{
    int i;
    *h=(treaptable*)malloc(sizeof(treaptable));
    (*h)->nr_buckets=50;
    (*h)->hfunc=hfunc;
    (*h)->Table=(Treap_node**)malloc(50*sizeof(Treap_node*));
    for(i=0;i<50;i++)
    {
        (*h)->Table[i]=NULL;
    }
    (*h)->size=50; 
}

void insert_Treaptable(char *o,treaptable **h)
{
    unsigned int bucket=hfunc(o);
    printf("%u\n",bucket);
    insert_Treap((*h)->Table[bucket],o,0);
}

int find_Treap(char *o, Treap_node *n)
{
    if(n!=NULL)
    {
        if(!strcmp(n->key,o))
        {
            return 1;
        }
        if(strcmp(n->key,o)>0)
            find_Treap(o,n->right);
        else
            find_Treap(o,n->left);
    }
    return 0;
}

void delete_Treapnode(char *o, Treap_node**t)
{
    unsigned int bucket=hfunc(o);
    stergere(&(*t),o);
}

void free_treaptable(treaptable **t)
{
    for(int i=0;i<50;i++)
    {
        free_Treap(&(*t)->Table[i]);
    }
    free((*t)->Table);
    free(*t);
}

int main()
{
    hashtable *h;
    init_Hash(&h);
    char sir[101];
    FILE *fis,*f2;
    fis=fopen("fisier.in","r");
    f2=fopen("out_test.out","w");
    while(fgets(sir,101,fis))
    {
        // scapam de \n
        sir[strlen(sir)-2]='\0';
        insert(sir,&h);
    }
    print_hashtable(h,f2);
    fprintf(f2,"\n\niteratia2\n");
    fprintf(f2,"\n%d\n",find("liverpool",h));
    fclose(fis);
    fclose(f2);
    return 0;
}