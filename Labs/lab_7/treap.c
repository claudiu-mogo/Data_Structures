#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treap_node {
    int key, priority,rad;
    struct Treap_node *left ,*right, *parent;
    int nr_nodes; // numarul de noduri din subarborele curent
} Treap_node ;

void init(Treap_node **tr)
{
    *tr=(Treap_node *)malloc(sizeof(Treap_node));
    (*tr)->left=(*tr)->right=(*tr)->parent=NULL;
    (*tr)->key=(*tr)->priority=(*tr)->nr_nodes=(*tr)->rad=0;
}

void free_Treap(Treap_node **tr)
{
    if((*tr)!=NULL)
    {
        free_Treap(&((*tr)->left));
        free_Treap(&((*tr)->right));
        free(*tr);
    }
}

void rotire_stanga(Treap_node** n) 
{
    Treap_node *t = (*n)->left;
    (*n)->left=t->right; 
    t->right = *n;
    *n = t;
}

void rotire_dreapta(Treap_node** n)
{
    Treap_node *t=(*n)->right;
    (*n)->right=t->left;
    t->left=*n;
    *n=t;
}

void balance(Treap_node** n)
{
    if((*n)->left->priority>(*n)->priority)
    {
        rotire_stanga(&(*n));
    }
    else
    {
        if((*n)->right->priority>(*n)->priority)
            rotire_dreapta(&(*n));
    }
}

void insert(Treap_node *tr,int key,int priority)
{
    if(tr->parent==NULL&&tr->rad==0)
    {
        tr->key=key;
        tr->priority=priority;
        tr->rad=1;
        tr->nr_nodes=0;
        return;
    }
    Treap_node *node;
    init(&node);
    node->key=key;
    node->priority=priority;
    if(tr->left==NULL&&key<tr->key)
    {
        tr->nr_nodes++;
        tr->left=node;
        node->parent=tr;
        if(tr->priority<node->priority)
            rotire_stanga(&tr);
        return;
    }
    if(tr->right==NULL&&key>tr->key)
    {
        tr->nr_nodes++;
        tr->right=node;
        node->parent=tr;
        if(tr->priority<node->priority)
            rotire_dreapta(&tr);
        return;
    }
    if(key>tr->key)
    {
        free(node);
        tr->nr_nodes++;
        insert(tr->right,key,priority);
        if(tr->priority<node->priority)
            rotire_dreapta(&tr);
        balance(&tr);
    }
    if(key<tr->key)
    {
        free(node);
        tr->nr_nodes++;
        insert(tr->left,key,priority);
        if(tr->priority<node->priority)
            rotire_stanga(&tr);
        balance(&tr);
    }
}

void stergere(Treap_node **tr,int key)
{
    if(*tr==NULL)
        return;
    if(key<(*tr)->key)
        stergere(&((*tr)->left),key);
    else
    {
        if(key>(*tr)->key)
            stergere(&((*tr)->right),key);
        else
        {
            if((*tr)->right==NULL&&(*tr)->left==NULL)
            {
                free((*tr));
                (*tr)=NULL;
            }
            else
            {
                if((*tr)->left->priority>(*tr)->right->priority)
                    rotire_stanga(&tr);
                else
                    rotire_dreapta(&tr);
                stergere(&tr,key);
            }
        }
    }

}

void print_k_key(Treap_node *t,int k)
{
    if(k>t->nr_nodes)
        return;
    if(k==0||k==t->left->nr_nodes+1)
        printf("%d",t->key);
    if(t->left&&k<t->left->nr_nodes+1)
        print_k_key(t->left,k);
    else
    {
        print_k_key(t->right,k-t->left->nr_nodes-2);
    }
}

void print_in_order(Treap_node *tree)
{
    if(tree!=NULL)
    {
        print_in_order(tree->left);
        printf("%d ",tree->key);
        printf("%d ",tree->priority);
        print_in_order(tree->right);
    }
}

void print_pre_order(Treap_node *tree)
{
    if(tree!=NULL)
    {
        printf("%d ",tree->key);
        printf("%d ",tree->priority);
        print_pre_order(tree->left);
        print_pre_order(tree->right);
    }
}

void print_post_order(Treap_node *tree)
{
    if(tree!=NULL)
    {
        print_post_order(tree->left);
        print_post_order(tree->right);
        printf("%d ",tree->key);
        printf("%d ",tree->priority);
    }
}

int main()
{
    int n,i,cheie,prioritate;
    Treap_node *t;
    init(&t);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d%d",&cheie,&prioritate);
        insert(t,cheie,prioritate);
    }
    print_pre_order(t);
    free_Treap(&t);
    return 0;
}