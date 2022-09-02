#include <stdio.h>
#include <stdlib.h>

//am facut kosaraju

typedef struct node {
    int val;
    struct node* next;
} node; 

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

typedef struct TList {
    node* head;
    int len;
} TList;

void init_list(node **list)
{
    *list=(node *)malloc(sizeof(node));
    (*list)->val=0;
    (*list)->next=NULL;
}

void free_list(node **list)
{
    node *p1;
    while((*list)!=NULL)
    {
        p1=(*list);
        (*list)=(*list)->next;
        free(p1);
    }
    free(*list);
}

void add_start(node **list, int val,int *verif)
{
    if(*verif==0)
    {
        (*list)->val=val;
        (*verif)=1;
        return;
    }
    node* new_node;
    new_node=(node *)malloc(sizeof(node));
    new_node->next=NULL;
    new_node->val=val;
    new_node->next=*list;
    *list=new_node;
    //fprintf(stdout,"%d\n",(*list)->val);
}

void print_int_list(node *list)
{
    node *p=list;
    while(p!=NULL)
    {
        printf("%d ",p->val);
        p=p->next;
    }
    printf("\n");
}

int length(node *head)
{
    node *p=head;
    int i=0;
    while(p!=NULL)
    {
        i++;
        p=p->next;
    }
    return i;
}

typedef struct Queue {
    node *head, *tail;
    int len;
} Queue;

void init_Queue(Queue** q)
{
    *q=(Queue*)malloc(sizeof(Queue));
    (*q)->head=NULL;
    (*q)->tail=NULL;
    (*q)->len=0;
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

int add_queue (Queue *q, int val)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->val=val;
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

int pop_queue(Queue *q)
{
    if(q->len>0)
    {
        node *p=q->head;
        q->head=q->head->next;
        int v=p->val;
        free(p);
        q->len--;
        return v;
    }
    exit(1);
}

void print_Q(Queue *q)
{
    node *p=q->head;
    while(p!=NULL)
    {
        printf("%d ",p->val);
        p=p->next;
    }
    printf("\n");
}

int get_xth_node(node *q,int x)
{
    int i;
    node *p=q;
    for(i=0;i<x;i++)
        p=p->next;
    return p->val;
}

int is_empty_Queue(Queue *q)
{
    if(q->len==0)
        return 1;
    return 0;
}

void bfs(graph *g,int source,int n)
{
    Queue *q;
    int dist[50],x,visited[50],i;
    for(i=0;i<n;i++)
    {
        visited[i]=0;
        dist[i]=-1;
    }
    init_Queue(&q);
    add_queue(q,source);
    dist[source]=0;
    while(!is_empty_Queue(q))
    {
        x=pop_queue(q);
        visited[x]=1;
        int nr_neigh=length(g->neighbours[x]);
        for(i=0;i<nr_neigh;i++)
        {
            if(!visited[get_xth_node(g->neighbours[x],i)])
            {
                add_queue(q,get_xth_node(g->neighbours[x],i));
                dist[get_xth_node(g->neighbours[x],i)]=dist[x]+1;
            }
        }
    }
    printf("distante bfs fata de nodul %d: ",source);
    for(i=0;i<n;i++)
        printf("%d ",dist[i]);
    printf("\n");
    free_Queue(&q);
}

typedef struct Stack {
    node *top;
    int len;
} Stack;

void init_Stack(Stack** s)
{
    *s=(Stack*)malloc(sizeof(Stack));
    (*s)->top=NULL;
    (*s)->len=0;
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

int add_stack (Stack *s, int val)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->val=val;
    new_node->next=NULL;
    new_node->next=s->top;
    s->top=new_node;
    s->len++;
    return 1;
}

int pop_stack(Stack *s)
{
    if(s->len>0)
    {
        node *p=s->top;
        s->top=s->top->next;
        int v=p->val;
        free(p);
        s->len--;
        return v;
    }
    exit(1);
}

void print_Stack(Stack *s)
{
    node *p=s->top;
    while(p!=NULL)
    {
        printf("%d ",p->val);
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

void dfs(graph *g,int nod,int n,int *visited,int *discover_time,int *finish,int time,Stack *s)
{
    int x,i;
    visited[nod]=1;
    discover_time[nod]=time++;
    int nr_neigh=length(g->neighbours[nod]);
    //printf("nr_vecini:%d\n",nr_neigh);
    for(i=0;i<nr_neigh;i++)
    {
        //printf("nod vecin:%d\n",get_xth_node(g->neighbours[nod],i));
        if(!visited[get_xth_node(g->neighbours[nod],i)])
        {
            dfs(g,get_xth_node(g->neighbours[nod],i),n,visited,discover_time,finish,time,s);
        }
    }
    finish[nod]=time++;
    add_stack(s,nod);
}

void apel_dfs(graph *g,int n,int *visited,int *discover_time,int *finish,int time,Stack *s)
{
    int i;
    for(i=0;i<n;i++)
        visited[i]=0;
    for(i=0;i<n;i++)
    {
        if(!visited[i])
            dfs(g,i,n,visited,discover_time,finish,time,s);
    }
}

int tare_conex(graph *g,int nod,int n,int *visited,int *discover_time,int *finish,int time,Stack *s,graph *tr)
{
    int ctc=0,*visited2,i;
    visited2=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        visited2[i]=0;
    apel_dfs(g,n,visited,discover_time,finish,time,s);
    int *useless_discover,*useless_finish,timp;
    useless_discover=malloc(n*sizeof(int));
    useless_finish=malloc(n*sizeof(int));
    Stack *stk;
    init_Stack(&stk);
    while(!is_empty_Stack(s))
    {
        int x=pop_stack(s);
        if(!visited2[x])
        {
            apel_dfs(tr,n,visited2,useless_discover,useless_finish,timp,stk);
            ctc++;
        }
    }
    free(visited2);
    free(useless_discover);
    free(useless_finish);
    free_Stack(&stk);
    return ctc;
}

int main()
{
    int i,j,n,m,nod_curent,vecin,*caract,*visited,*discover_time,*finish,*caract2;
    FILE *f1=fopen("graf1.in","r");
    fscanf(f1,"%d%d",&n,&m);
    graph *gr,*transpose;
    transpose=malloc(sizeof(graph));
    transpose->neighbours=malloc(n*sizeof(node*));
    gr=malloc(sizeof(graph));
    gr->neighbours=malloc(n*sizeof(node*));
    visited=malloc(n*sizeof(int));
    discover_time=malloc(n*sizeof(int));
    finish=malloc(n*sizeof(int));
    caract=malloc(n*sizeof(int));
    caract2=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        caract[i]=0;
        caract2[i]=0;
    }
    for(i=0;i<n;i++)
    {
        init_list(&gr->neighbours[i]);
        init_list(&transpose->neighbours[i]);
    }
    for(i=0;i<m;i++)
    {
        fscanf(f1,"%d%d",&nod_curent,&vecin);
        //fprintf(stdout,"%d %d\n",nod_curent,vecin);
        add_start(&gr->neighbours[nod_curent],vecin,&caract[nod_curent]);
        add_start(&transpose->neighbours[vecin],nod_curent,&caract2[vecin]);
        //fprintf(stdout,"%d\n",gr->neighbours[nod_curent]->val);
    }
    printf("Vecini:\n");
    for(i=0;i<n;i++)
    {
        printf("%d-> ",i);
        print_int_list(gr->neighbours[i]);
    }
    bfs(gr,2,n);
    Stack *s;
    init_Stack(&s);
    //dfs(gr,2,n,visited,discover_time,finish,0,s);
    printf("%d\n",tare_conex(gr,2,n,visited,discover_time,finish,0,s,transpose));
    //afisam timpii (ii avem in discover si finish)
    for(i=0;i<n;i++)
    {
        printf("%d %d\n",discover_time[i],finish[i]);
    }

    for(i=0;i<n;i++)
    {
        free_list(&gr->neighbours[i]);
    }
    free(gr->neighbours);
    free(gr);
    free(caract);
    for(i=0;i<n;i++)
    {
        free_list(&transpose->neighbours[i]);
    }
    free(transpose->neighbours);
    free(transpose);
    free(caract2);
    free(visited);
    free(discover_time);
    free(finish);
    free_Stack(&s);
    fclose(f1);
    return 0;
}