#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// heap.c contine functiile pt heap-ul de la dijkstra
// la dijkstra si bellman am luat nosul sursa 0
// nu era nimic de schimbat daca era sa dau un index sursa drept parametru,
// dar n-am mai vrut sa bag mai mult input
// am verificat toti algoritmii pe niste grafuri la care stiam outputul si sunt ok

typedef struct node {
    int val;
    float cost;
    struct node* next;
} node; 

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

void init_list(node **list)
{
    *list=(node *)malloc(sizeof(node));
    (*list)->val=0;
    (*list)->cost=0;
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

void add_start(node **list, int val,int *verif,float cost)
{
    if(*verif==0)
    {
        (*list)->val=val;
        (*list)->cost=cost;
        (*verif)=1;
        return;
    }
    node* new_node;
    new_node=(node *)malloc(sizeof(node));
    new_node->next=NULL;
    new_node->val=val;
    new_node->cost=cost;
    new_node->next=*list;
    *list=new_node;
    //fprintf(stdout,"%d\n",(*list)->val);
}

void print_int_list(node *list)
{
    node *p=list;
    while(p!=NULL)
    {
        printf("%d/%.1f  ",p->val,p->cost);
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

int get_xth_node(node *q,int x)
{
    int i;
    node *p=q;
    for(i=0;i<x;i++)
        p=p->next;
    return p->val;
}

float get_xth_cost(node *q,int x)
{
    int i;
    node *p=q;
    for(i=0;i<x;i++)
        p=p->next;
    return p->cost;
}

float minim(float a, float b)
{
    if(a>b)
        return b;
    return a;
}

void roy_floyd(graph *g, float **d,int n)
{
    int i,k,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            d[i][j]=10000;
        }
    }
    for(i=0;i<n;i++)
    {
        int nr_neigh=length(g->neighbours[i]);
        for(j=0;j<nr_neigh;j++)
        {
            d[i][get_xth_node(g->neighbours[i],j)]=get_xth_cost(g->neighbours[i],j);
        }
    }
    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                d[i][j]=minim(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}

void search_pre_order(heapnode *h,int index,float new_dist)
{
    if(h!=NULL)
    {
        if(index==h->index)
        {
            h->val=new_dist;
            return ;
        }
        search_pre_order(h->left,index,new_dist);
        search_pre_order(h->right,index,new_dist);
    }
}

//Dijkstra pt sursa 0
void dijkstra(graph *g,int n)
{
    Heap *h;
    int i;
    init(&h);
    int poz[n];
    float dist[n];
    for(i=0;i<n;i++)
    {
        dist[i]=10000;
        poz[i]=-1;
    }
    dist[0]=0;
    poz[0]=h->no_heapnodes+1;
    insert(h,0,0);
    while(h->no_heapnodes!=0)
    {
        int nod;//=remove_root(h);
        if(h->no_heapnodes==1)
        {
            nod=h->root->index;
            free(h->root);
            free(h);
            init(&h);
        }
        else
            nod=remove_root(h);
        int nr_neigh=length(g->neighbours[nod]);
        int x;
        for(x=0;x<nr_neigh;x++)
        {
            if(dist[get_xth_node(g->neighbours[nod],x)]>dist[nod]+get_xth_cost(g->neighbours[nod],x))
            {
                dist[get_xth_node(g->neighbours[nod],x)]=dist[nod]+get_xth_cost(g->neighbours[nod],x);
                if(poz[get_xth_node(g->neighbours[nod],x)]==-1)
                {
                    poz[get_xth_node(g->neighbours[nod],x)]=h->no_heapnodes+1;
                    insert(h,dist[get_xth_node(g->neighbours[nod],x)],get_xth_node(g->neighbours[nod],x));
                }
                else
                {
                    search_pre_order(h->root,get_xth_node(g->neighbours[nod],x),dist[get_xth_node(g->neighbours[nod],x)]);
                }
            }
        }
    }
    printf("Dijkstra pt 0:\n");
    for(i=0;i<n;i++)
        printf("%.1f ",dist[i]);
    free(h);
}

//Bellman-Ford cu sursa 0

void bellman(graph *g,int n)
{
    float d2[n];
    int i,j;
    for(i=0;i<n;i++)
        d2[i]=10000;
    d2[0]=0;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n;j++)
        {
            int nr_neigh=length(g->neighbours[j]);
            for(int k=0;k<nr_neigh;k++)
            {
                if(d2[get_xth_node(g->neighbours[j],k)]>d2[j]+get_xth_cost(g->neighbours[j],k))
                {
                    d2[get_xth_node(g->neighbours[j],k)]=d2[j]+get_xth_cost(g->neighbours[j],k);
                }
            }
        }
    }
    for(j=0;j<n;j++)
    {
        int nr_neigh=length(g->neighbours[j]);
        for(int k=0;k<nr_neigh;k++)
        {
            if(d2[get_xth_node(g->neighbours[j],k)]>d2[j]+get_xth_cost(g->neighbours[j],k))
            {
                printf("ciclu negativ\n");
                return;
            }
        }
    }
    printf("Bellman cu sursa 0:\n");
    for(i=0;i<n;i++)
        printf("%.1f ",d2[i]);
}

int main()
{
    int i,j,n,m,*visited,vecin,*caract,nod_curent;
    float cost;
    graph *g;
    FILE *f1=fopen("graf1.in","r");
    fscanf(f1,"%d%d",&n,&m);
    g=malloc(sizeof(graph));
    g->neighbours=malloc(n*sizeof(node*));
    visited=malloc(n*sizeof(int));
    caract=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        init_list(&g->neighbours[i]);
        caract[i]=0;
    }
    for(i=0;i<m;i++)
    {
        fscanf(f1,"%d%d%f",&nod_curent,&vecin,&cost);
        add_start(&g->neighbours[nod_curent],vecin,&caract[nod_curent],cost);
    }
    printf("Vecini:\n");
    for(i=0;i<n;i++)
    {
        printf("%d-> ",i);
        print_int_list(g->neighbours[i]);
    }
    free(visited);
    free(caract);
    /////////////////
    // Roy_Floyd
    float **d;
    d=malloc(n*sizeof(float*));
    for(i=0;i<n;i++)
        d[i]=malloc(n*sizeof(float));
    roy_floyd(g,d,n);
    printf("Roy-Floyd:\n");
    for(i=0;i<n;i++)
    {
        printf("%d->  ",i);
        for(j=0;j<n;j++)
        {
            printf("%.1f ",d[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<n;i++)
        free(d[i]);
    free(d);
    ////////////////////
    // Dijkstra cu sursa 0
    dijkstra(g,n);
    printf("\n");
    // Bellman-Ford
    bellman(g,n);
    for(i=0;i<n;i++)
    {
        free_list(&g->neighbours[i]);
        free(g->neighbours[i]);
    }
    free(g->neighbours);
    free(g);
    fclose(f1);
    return 0;
}