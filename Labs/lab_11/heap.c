#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void init(Heap **h)
{
    (*h)=malloc(sizeof(Heap));
    (*h)->root=NULL;
    (*h)->no_heapnodes=0;
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

void to_up(Heap *h,heapnode *p)
{
    if(p!=h->root&&p->val<p->parent->val)
    {
        int aux=p->val;
        p->val=p->parent->val;
        p->parent->val=aux;
        int aux2=p->index;
        p->index=p->parent->index;
        p->parent->index=aux2;
        to_up(h,p->parent);
    }
}

void insert(Heap *h,int val,int index)
{
    if(h->root==NULL)
    {
        h->root=malloc(sizeof(heapnode));
        h->no_heapnodes=1;
        h->root->val=val;
        h->root->index=index;
        h->root->left=h->root->right=h->root->parent=NULL;
        return;
    }
    h->no_heapnodes++;
    char sir[9];
    dec_to_bin(h->no_heapnodes,sir);
    int i=0;
    heapnode *p=h->root;
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
        p->left=malloc(sizeof(heapnode));
        p->left->val=val;
        p->left->index=index;
        p->left->parent=p;
        p->left->left=p->left->right=NULL;
        to_up(h,p->left);
    }
    else
    {
        p->right=malloc(sizeof(heapnode));
        p->right->val=val;
        p->right->index=index;
        p->right->parent=p;
        p->right->left=p->right->right=NULL;
        to_up(h,p->right);
    }
}

void heapify(heapnode *p)
{
    if(p==NULL)
        return;
    int l=0,r=0;
    int smallest_son=10000;
    if(p->left&&p->left->val<smallest_son)
    {
        smallest_son=p->left->val;
        l=1;
    }
    if(p->right&&p->right->val<smallest_son)
    {
        smallest_son=p->right->val;
        r=1;
    }
    if(r==1&&p->right->val<p->val)
    {
        int aux2=p->right->val;
        p->right->val=p->val;
        p->val=aux2;
        int aux=p->right->index;
        p->right->index=p->index;
        p->index=aux;
        heapify(p->right);
    }
    else if(l==1&&p->left->val<p->val)
    {
        int aux2=p->left->val;
        p->left->val=p->val;
        p->val=aux2;
        int aux=p->left->index;
        p->left->index=p->index;
        p->index=aux;
        heapify(p->left);
    }
}

int remove_root(Heap *h)
{
    if(h->root==NULL)
        return -1;
    char sir[9];
    dec_to_bin(h->no_heapnodes,sir);
    int i=0,aux,aux2;
    heapnode *p=h->root;
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
        aux2=h->root->index;
        h->root->index=p->left->index;
        p->left->index=aux2;
        free(p->left);
        p->left=NULL;
    }
    else
    {
        aux=h->root->val;
        h->root->val=p->right->val;
        p->right->val=aux;
        aux2=h->root->index;
        h->root->index=p->right->index;
        p->right->index=aux2;
        free(p->right);
        p->right=NULL;
    }
    heapify(h->root);
    h->no_heapnodes--;
    return aux2;
}

void search_pre_order(heapnode *h,int index,int new_dist)
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