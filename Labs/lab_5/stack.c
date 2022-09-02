#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int data;
    struct node* next;
} node;

typedef struct Stack {
    node *top;
    int len;
} Stack;

typedef struct Queue {
    node *head, *tail;
    int len;
} Queue;

void init_Stack(Stack** s)
{
    *s=(Stack*)malloc(sizeof(Stack));
    (*s)->top=NULL;
    (*s)->len=0;
}

void init_Queue(Queue** q)
{
    *q=(Queue*)malloc(sizeof(Queue));
    (*q)->head=NULL;
    (*q)->tail=NULL;
    (*q)->len=0;
}

void free_Stack(Stack** s)
{
    node *p;
    while((*s)->top!=NULL)
    {
        p=(*s)->top;
        (*s)->top=(*s)->top->next;
        free(p);
    }
    free(*s);
}

void free_Queue(Queue** q)
{
    node *p;
    while((*q)->head!=NULL)
    {
        p=(*q)->head;
        (*q)->head=(*q)->head->next;
        free(p);
    }
    free(*q);
}

int add_stack (Stack *s, int val)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->data=val;
    new_node->next=NULL;
    new_node->next=s->top;
    s->top=new_node;
    s->len++;
    return 1;
}

int add_queue (Queue *q, int val)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->data=val;
    new_node->next=NULL;
    if(q->len==0)
    {
        q->tail=q->head=new_node;
    }
    else
    {
        q->tail->next=new_node;
        q->tail=new_node;
    }
    q->len++;
    return 1;
}

int pop_stack(Stack *s)
{
    if(s->len>0)
    {
        node *p=s->top;
        s->top=s->top->next;
        int v=p->data;
        free(p);
        s->len--;
        return v;
    }
    exit(1);
}

int pop_queue(Queue *q)
{
    if(q->len>0)
    {
        node *p=q->head;
        q->head=q->head->next;
        int v=p->data;
        free(p);
        q->len--;
        return v;
    }
    exit(1);
}

void print_Stack(Stack *s)
{
    node *p=s->top;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

void print_Q(Queue *q)
{
    node *p=q->head;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int is_empty_Stack(Stack *s)
{
    if(s->len==0)
        return 1;
    return 0;
}

int is_empty_Queue(Queue *q)
{
    if(q->len==0)
        return 1;
    return 0;
}

void Radix(int *v,int n)
{
    int i,maxel=v[0],nrdigmax=0,j;
    for(i=1;i<n;i++)
    {
        if(v[i]>maxel)
            maxel=v[i];
    }
    while(maxel!=0)
    {
        nrdigmax++;
        maxel=maxel/10;
    }
    Queue *q[10];
    for(j=0;j<nrdigmax;j++)
    {
        for(i=0;i<=9;i++)
            init_Queue(&q[i]);
        int div=1,categorie,poz=0;
        for(i=0;i<j;i++)
            div*=10;
        for(i=0;i<n;i++)
        {
            categorie=(v[i]/div)%10;
            add_queue(q[categorie],v[i]);
        }
        for(i=0;i<=9;i++)
        {
            for(categorie=0;categorie<=9;categorie++)
            {
                while (!is_empty_Queue(q[categorie]))
                {
                    v[poz++]=pop_queue(q[categorie]);
                }
                
            }
        }
        
        for(i=0;i<=9;i++)
            free_Queue(&q[i]); 
    }
}

int main()
{
    int i,n,x,k,v[101];
    srand(time(0));
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        //scanf("%d",&v[i]);
        x=(rand())%10000;
        while (!x)
        {
            x=(rand())%10000;
        }
        //printf("%d ",x);
        v[i]=x;
    }
        //scanf("%d",&v[i]);
    Radix(v,n);
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
    return 0;
}