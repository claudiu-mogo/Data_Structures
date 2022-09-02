#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList {
    node *sentinel;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList **list)
{
    *list=(TDoubleLinkedList *)malloc(sizeof(TDoubleLinkedList));
    (*list)->sentinel=(node *)malloc(sizeof(node));
    (*list)->sentinel->next=NULL;
    (*list)->sentinel->prev=NULL;
    (*list)->len=0;
}

int add(TDoubleLinkedList *list, int n, void* data)
{
    if(n>list->len||n<0)
        return -1;
    node *new_node=(node *)malloc(sizeof(node));
    new_node->data=data;
    new_node->next=NULL;
    new_node->prev=NULL;
    if(list->len==0)
    {
        list->sentinel->next=new_node;
        list->sentinel->prev=new_node;
        new_node->next=new_node->prev=list->sentinel;
        list->len++;
        return 1;
    }
    if(n==0)
    {
        new_node->next=list->sentinel->next;
        new_node->prev=list->sentinel;
        list->sentinel->next->prev=new_node;
        list->sentinel->next=new_node;
        list->len++;
        return 1;
    }
    if(list->len==n)
    {
        new_node->prev=list->sentinel->prev;
        new_node->next=list->sentinel;
        list->sentinel->prev->next=new_node;
        list->sentinel->prev=new_node;
        list->len++;
        return 1;
    }
    if(n<list->len/2)
    {
        node *p=list->sentinel->next;
        for(int i=0;i<n-1;i++)
            p=p->next;
        new_node->next=p->next;
        new_node->prev=p;
        p->next->prev=new_node;
        p->next=new_node;
        list->len++;
    } 
    else
    {
        node *p=list->sentinel->prev;
        for(int i=list->len-1;i>n-1;i--)
            p=p->prev;
        new_node->next=p->next;
        new_node->prev=p;
        p->next->prev=new_node;
        p->next=new_node;
        list->len++;
    }
    return 1;
}

int removenode(TDoubleLinkedList *list, int n)
{
    if(n>=list->len||n<0)
        return -1;
    if(n==0)
    {
        node *q=list->sentinel->next;
        list->sentinel->next=list->sentinel->next->next;
        list->sentinel->next->prev=list->sentinel;
        free(q->data);
        free(q);
        list->len--;
        return 1;
    }
    if(n==list->len-1)
    {
        node *p=list->sentinel->prev;
        list->sentinel->prev=list->sentinel->prev->prev;
        list->sentinel->prev->next=list->sentinel;
        free(p->data);
        free(p);
        list->len--;
        return 1;
    }
    if(n<list->len/2)
    {
        node *p=list->sentinel->next;
        for(int i=0;i<n-1;i++)
            p=p->next;
        node *q=p->next;
        p->next=p->next->next;
        p->next->prev=p;
        free(q->data);
        free(q);
        list->len--;
    }
    else
    {
        node *p=list->sentinel->prev;
        for(int i=list->len-1;i>n-1;i--)
            p=p->prev;
        node *q=p->next;
        p->next=p->next->next;
        p->next->prev=p;
        free(q->data);
        free(q);
        list->len--;
    }
    return 1;
}

void print_int_list(TDoubleLinkedList *list)
{
    node *p=list->sentinel->next;
    while(p!=list->sentinel)
    {
        printf("%d ",*(int *)(p->data));
        p=p->next;
    }
    printf("\n");
}

void free_list(TDoubleLinkedList **list)
{
    node *p,*q=(*list)->sentinel->next;
    while(q!=(*list)->sentinel)
    {
        p=q;
        q=q->next;
        free(p->data);
        free(p);
    }
    free((*list)->sentinel->data);
    free((*list)->sentinel);
    free(*list);
}

int main()
{
    TDoubleLinkedList *list;
    init(&list);
    int i,n,*val,poz,ret;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        val=(int *)malloc(sizeof(int));
        scanf("%d",val);
        scanf("%d",&poz);
        ret=add(list,poz,val);
        print_int_list(list);
    }
    print_int_list(list);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&poz);
        ret=removenode(list,poz);
        print_int_list(list);
    }
    print_int_list(list);
    free_list(&list);
    return 0;
}