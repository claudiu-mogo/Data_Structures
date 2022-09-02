#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


// am nodurile numerotate de la 0
typedef struct node {
    int val;
    int cost;
    struct node* next;
} node; 

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

typedef struct ama_node{
    int val;
    int children_count;
    struct ama_node** children;
}ama_node;

void add_child(ama_node *parent,int val)
{
    if(parent->children_count==0)
    {
        parent->children_count++;
        parent->children=malloc(sizeof(ama_node*));
        parent->children[0]=malloc(sizeof(ama_node));
        parent->children[0]->val=val;
        parent->children[0]->children_count=0;
    }
    else
    {
        parent->children_count++;
        parent->children=realloc(parent->children,parent->children_count*sizeof(ama_node*));
        parent->children[parent->children_count-1]=malloc(sizeof(ama_node));
        parent->children[parent->children_count-1]->val=val;
        parent->children[parent->children_count-1]->children_count=0;
    }
}

void add_ama(ama_node *root,int parent,int val)
{
    if(root!=NULL)
    {
        if(root->val==parent)
            add_child(root,val);
        for(int i=0;i<root->children_count;i++)
        {
            add_ama(root->children[i],parent,val);
        }
    }
}

void free_ama(ama_node *root)
{
    if(root!=NULL)
    {
        for(int i=0;i<root->children_count;i++)
        {
            free_ama(root->children[i]);
        }
        if(root->children_count>0)
            free(root->children);
        free(root);
    }
}

void print_ama(ama_node *root)
{
    if(root->children_count>0)
    {
        printf("%d are copiii: ",root->val);
        for(int i=0;i<root->children_count;i++)
        {
            printf("%d ",root->children[i]->val);
        }
        printf("\n");
        for(int i=0;i<root->children_count;i++)
        {
            print_ama(root->children[i]);
        }
    }
}

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

void add_start(node **list, int val,int *verif,int cost)
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
}

void print_int_list(node *list)
{
    node *p=list;
    while(p!=NULL)
    {
        printf("%d/%d  ",p->val,p->cost);
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

int get_xth_cost(node *q,int x)
{
    int i;
    node *p=q;
    for(i=0;i<x;i++)
        p=p->next;
    return p->cost;
}

int minim(int a, int b)
{
    if(a>b)
        return b;
    return a;
}

int prim(graph *g,int n, ama_node*root)
{
    Heap *h;
    int i;
    init(&h);
    int poz[n],p[n],total_cost=0;;
    int dist[n];
    for(i=0;i<n;i++)
    {
        dist[i]=10000;
        poz[i]=-1;
        p[i]=-1;
    }
    dist[0]=0;
    poz[0]=h->no_heapnodes+1;
    insert(h,0,0);
    while(h->no_heapnodes!=0)
    {
        int nod;
        if(h->no_heapnodes==1) // avem probleme cand ramane heapul gol
        {
            nod=h->root->index;
            free(h->root);
            free(h);
            init(&h);
        }
        else
            nod=remove_root(h);
        if(nod!=0)
        {
            printf("%d cu parinte %d\n",nod,p[nod]);
            add_ama(root,p[nod],nod);
            total_cost+=dist[nod];
        }
        int nr_neigh=length(g->neighbours[nod]);
        int x;
        for(x=0;x<nr_neigh;x++)
        {
            if(get_xth_cost(g->neighbours[nod],x)<dist[get_xth_node(g->neighbours[nod],x)])
            {
                dist[get_xth_node(g->neighbours[nod],x)]=get_xth_cost(g->neighbours[nod],x);
                p[get_xth_node(g->neighbours[nod],x)]=nod;
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
    free(h);
    return total_cost;
}

int main()
{
    int i,j,n,m,*visited,vecin,*caract,nod_curent,cost;
    graph *g;
    FILE *f1=fopen("graf.in","r");
    ama_node *root;
    root=malloc(sizeof(ama_node));
    fscanf(f1,"%d%d",&n,&m);
    g=malloc(sizeof(graph));
    g->neighbours=malloc(n*sizeof(node*));
    caract=malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        init_list(&g->neighbours[i]);
        caract[i]=0;
    }
    for(i=0;i<m;i++)
    {
        fscanf(f1,"%d%d%d",&nod_curent,&vecin,&cost);
        add_start(&g->neighbours[nod_curent],vecin,&caract[nod_curent],cost);
    }
    root->val=0;
    root->children_count=0;
    printf("%d\n",prim(g,n,root));
    print_ama(root);
    free_ama(root);
    for(i=0;i<n;i++)
    {
        free_list(&g->neighbours[i]);
        free(g->neighbours[i]);
    }
    free(g->neighbours);
    free(g);
    free(caract);
    fclose(f1);
    return 0;
}