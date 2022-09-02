#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left, *right,*parent;
} node;

typedef struct Heap {
    int no_nodes;
    struct node *root;
} Heap;

void init(Heap **h)
{
    (*h)=malloc(sizeof(Heap));
    (*h)->root=NULL;
    (*h)->no_nodes=0;
}

void dec_to_bin(int n, char *s)
{
    int i;
    for(i=0;i<8;i++)
        s[i]='0';
    while(n)
    {
        s[--i]=n%2+'0';
        n/=2;
    }
    s[8]='\0';
}

void to_up(Heap *h,node *p)
{
    if(p!=h->root&&p->val>p->parent->val)
    {
        int aux=p->val;
        p->val=p->parent->val;
        p->parent->val=aux;
        to_up(h,p->parent);
    }
}

void insert(Heap *h,int val)
{
    if(h->root==NULL)
    {
        h->root=malloc(sizeof(node));
        h->no_nodes=1;
        h->root->val=val;
        h->root->left=h->root->right=h->root->parent=NULL;
        return;
    }
    h->no_nodes++;
    char sir[9];
    dec_to_bin(h->no_nodes,sir);
    int i=0;
    node *p=h->root;
    while(sir[i]!='1')
    {
        i++;
    }
    i++;
    while(i<7)
    {
        if(sir[i]=='0')
            p=p->left;
        else
            p=p->right;
        i++;
    }
    if(sir[i]=='0')
    {
        p->left=malloc(sizeof(node));
        p->left->val=val;
        p->left->parent=p;
        p->left->left=p->left->right=NULL;
        to_up(h,p->left);
    }
    else
    {
        p->right=malloc(sizeof(node));
        p->right->val=val;
        p->right->parent=p;
        p->right->left=p->right->right=NULL;
        to_up(h,p->right);
    }
}

void heapify(node *p)
{
    if(p==NULL)
        return;
    int largest_son=-1,l=0,r=0;
    if(p->left&&p->left->val>largest_son)
    {
        largest_son=p->left->val;
        l=1;
    }
    if(p->right&&p->right->val>largest_son)
    {
        largest_son=p->right->val;
        r=1;
    }
    if(r==1&&p->right->val>p->val)
    {
        int aux=p->right->val;
        p->right->val=p->val;
        p->val=aux;
        heapify(p->right);
    }
    else if(l==1&&p->left->val>p->val)
    {
        int aux=p->left->val;
        p->left->val=p->val;
        p->val=aux;
        heapify(p->left);
    }
}

int remove_root(Heap *h)
{
    if(h->root==NULL)
        return -1;
    char sir[9];
    dec_to_bin(h->no_nodes,sir);
    int i=0,aux;
    node *p=h->root;
    while(sir[i]!='1')
    {
        i++;
    }
    i++;
    while(i<7)
    {
        if(sir[i]=='0')
            p=p->left;
        else
            p=p->right;
        i++;
    }
    if(sir[i]=='0')
    {
        aux=h->root->val;
        h->root->val=p->left->val;
        p->left->val=aux;
        free(p->left);
        p->left=NULL;
    }
    else
    {
        aux=h->root->val;
        h->root->val=p->right->val;
        p->right->val=aux;
        free(p->right);
        p->right=NULL;
    }
    heapify(h->root);
    h->no_nodes--;
    return aux;
}

void print_pre_order(node *n)
{
    if(n!=NULL)
    {
        printf("%d ",n->val);
        print_pre_order(n->left);
        print_pre_order(n->right);
    }
}

int main()
{
    Heap *h;
    int n,x,i;
    scanf("%d",&n);
    init(&h);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        insert(h,x);
    }
    print_pre_order(h->root);
    printf("\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("%d\n",h->root->val);
        remove_root(h);
        //print_pre_order(h->root);
        printf("\n");
    }
    return 0;
}