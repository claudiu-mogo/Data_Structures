#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int weight, source, dest;
    struct node* next;
}node;

typedef struct TList
{
    int len;
    node *head;
}TList;

void init_list(TList **list)
{
    (*list)=malloc(sizeof(TList));
    (*list)->len=0;
    (*list)->head=malloc(sizeof(node));
    (*list)->head->next=NULL;
}

void free_list(TList **list)
{
    node *p1;
    while((*list)->head!=NULL)
    {
        p1=(*list)->head;
        (*list)->head=(*list)->head->next;
        free(p1);
    }
    free(*list);
}

void add_end(TList *list,int weight,int source,int dest)
{
    int i;
    node *p=list->head,*q;
    if(list->len==0)
    {
        p->next=NULL;
        p->weight=weight;
        p->source=source;
        p->dest=dest;
        list->len++;
        return;
    }
    while(p->next!=NULL)
    {
        p=p->next;
    }
    q=malloc(sizeof(node));
    q->next=NULL;
    q->weight=weight;
    q->source=source;
    q->dest=dest;
    p->next=q;
    list->len++;
}

node* remove_elem(TList *list,int weight,int source,int dest)
{
    int i;
    node *p=list->head,*q=list->head;
    if(list->len==1)
    {
        list->len--;
        return p;
    }
    if(p->weight==weight&&p->source==source&&p->dest==dest)
    {
        q=p;
        list->head=list->head->next;
        //printf("%d %d %d\n",p->source,p->dest,p->weight);
        list->len--;
        return q;
    }
    while(p!=NULL&&!(p->weight==weight&&p->source==source&&p->dest==dest))
    {
        q=p;
        p=p->next;
    }
    q->next=p->next;
    list->len--;
    //printf("%d %d %d\n",p->source,p->dest,p->weight);
    return p;
}

void sort_list(TList *list)
{
    node *p=list->head,*q=list->head,*aux;
    int min_weight=10000,so,de,i;
    TList *list2;
    init_list(&list2);
    while(list->len!=0)
    {
        p=list->head;
        min_weight=10000;
        while(p!=NULL)
        {
            if(p->weight<min_weight)
            {
                min_weight=p->weight;
                so=p->source;
                de=p->dest;
            }
            p=p->next;
        }
        q=remove_elem(list,min_weight,so,de);
        add_end(list2,q->weight,q->source,q->dest);
    }
    p=list2->head;
    while(p!=NULL)
    {
        add_end(list,p->weight,p->source,p->dest);
        p=p->next;
    }
    free_list(&list2);
}

void print_list(TList *list)
{
    node *p=list->head;
    while(p!=NULL)
    {
        printf("%d %d %d\n",p->source,p->dest,p->weight);
        p=p->next;
    }
}

int find(int i,int *tata)
{
    if (i == tata[i])
        return i;
    tata[i] = find(tata[i],tata);
    return tata[i];
}

void unite(int x, int y, int *tata)
{
    tata[find(x,tata)] = find(y,tata);
}

int kruskal(TList *list,int n)
{
    sort_list(list);
    node *p=list->head;
    int *tata,i,j,m,x,y,total_cost=0;
    tata=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        tata[i]=i;
    m=list->len;
    for(j=0;j<m;j++)
    {
        x=find(p->source,tata);
        y=find(p->dest,tata);
        if(x!=y)
        {
            unite(x,y,tata);
            // am afisat direct laturile din ama
            printf("%d %d %d\n",p->source,p->dest,p->weight);
            total_cost=total_cost+p->weight;
        }
        p=p->next;
    }
    free(tata);
    return total_cost;
}

int main()
{
    int i,j,we,so,de,m,n;
    FILE *f;
    TList *list;
    init_list(&list);
    f=fopen("graf.in","r");
    fscanf(f,"%d%d",&n,&m);
    for(i=0;i<m;i++)
    {
        fscanf(f,"%d%d%d",&so,&de,&we);
        add_end(list,we,so,de);
    }
    printf("%d\n",kruskal(list,n));
    free_list(&list);
    fclose(f);
    return 0;
}