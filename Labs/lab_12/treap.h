#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treap_node {
    int priority,rad;
    char *key;
    struct Treap_node *left ,*right, *parent;
    int nr_nodes; // numarul de noduri din subarborele curent
} Treap_node ;

void init_Treap(Treap_node **tr)
{
    *tr=(Treap_node *)malloc(sizeof(Treap_node));
    (*tr)->left=(*tr)->right=(*tr)->parent=NULL;
    (*tr)->priority=(*tr)->nr_nodes=(*tr)->rad=0;
    (*tr)->key=malloc(100*sizeof(char));
}

void free_Treap(Treap_node **tr)
{
    if((*tr)!=NULL)
    {
        free_Treap(&((*tr)->left));
        free_Treap(&((*tr)->right));
        free((*tr)->key);
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

void insert_Treap(Treap_node *tr,char* key,int priority)
{
    if(tr->parent==NULL&&tr->rad==0)
    {
        //tr->key=key;
        strcpy(tr->key,key);
        tr->priority=priority;
        tr->rad=1;
        tr->nr_nodes=0;
        return;
    }
    Treap_node *node;
    init_Treap(&node);
    //node->key=key;
    strcpy(node->key,key);
    node->priority=priority;
    //key<tr->key
    if(tr->left==NULL&&strcmp(key,tr->key)<0)
    {
        tr->nr_nodes++;
        tr->left=node;
        node->parent=tr;
        if(tr->priority<node->priority)
            rotire_stanga(&tr);
        return;
    }
    if(tr->right==NULL&&strcmp(key,tr->key)>0)
    {
        tr->nr_nodes++;
        tr->right=node;
        node->parent=tr;
        if(tr->priority<node->priority)
            rotire_dreapta(&tr);
        return;
    }
    if(strcmp(key,tr->key)>0)
    {
        free(node);
        tr->nr_nodes++;
        insert_Treap(tr->right,key,priority);
        if(tr->priority<node->priority)
            rotire_dreapta(&tr);
        balance(&tr);
    }
    if(strcmp(key,tr->key)<0)
    {
        free(node);
        tr->nr_nodes++;
        insert_Treap(tr->left,key,priority);
        if(tr->priority<node->priority)
            rotire_stanga(&tr);
        balance(&tr);
    }
}

void stergere(Treap_node **tr,char* key)
{
    if(*tr==NULL)
        return;
    if(strcmp(key,(*tr)->key)<0)
        stergere(&((*tr)->left),key);
    else
    {
        if(strcmp(key,(*tr)->key)>0)
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
                    rotire_stanga(&(*tr));
                else
                    rotire_dreapta(&(*tr));
                stergere(&(*tr),key);
            }
        }
    }

}

void print_k_key(Treap_node *t,int k)
{
    if(k>t->nr_nodes)
        return;
    if(k==0||k==t->left->nr_nodes+1)
        printf("%s\n",t->key);
    if(t->left&&k<t->left->nr_nodes+1)
        print_k_key(t->left,k);
    else
    {
        print_k_key(t->right,k-t->left->nr_nodes-2);
    }
}