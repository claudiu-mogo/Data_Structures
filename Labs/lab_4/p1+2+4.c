#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList {
    node *head;
    node *tail;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList **list)
{
    *list=(TDoubleLinkedList *)malloc(sizeof(TDoubleLinkedList));
    //(*list)->head=(node *)malloc(sizeof(node));
    //(*list)->tail=(node *)malloc(sizeof(node));
    (*list)->head=NULL;
    (*list)->tail=NULL;
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
        list->head=new_node;
        list->tail=new_node;
        list->len++;
        return 1;
    }
    if(n==0)
    {
        new_node->next=list->head;
        list->head->prev=new_node;
        list->head=new_node;
        list->len++;
        return 1;
    }
    if(list->len==n)
    {
        new_node->prev=list->tail;
        list->tail->next=new_node;
        list->tail=new_node;
        list->len++;
        return 1;
    }
    if(n<list->len/2)
    {
        node *p=list->head;
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
        node *p=list->tail;
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
        node *q=list->head;
        list->head=list->head->next;
        list->head->prev=NULL;
        free(q->data);
        free(q);
        list->len--;
        return 1;
    }
    if(n==list->len-1)
    {
        node *p=list->tail;
        list->tail=list->tail->prev;
        list->tail->next=NULL;
        free(p->data);
        free(p);
        list->len--;
        return 1;
    }
    if(n<list->len/2)
    {
        node *p=list->head;
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
        node *p=list->tail;
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
    node *p=list->head;
    while(p!=NULL)
    {
        printf("%d ",*(int *)(p->data));
        p=p->next;
    }
    printf("\n");
}

void print_string_list(TDoubleLinkedList *list)
{
    node *p=list->head;
    while(p!=NULL)
    {
        printf("%s ",(char *)(p->data));
        p=p->next;
    }
    printf("\n");
}

void free_list(TDoubleLinkedList **list)
{
    node *p;
    while((*list)->head!=NULL)
    {
        p=(*list)->head;
        (*list)->head=(*list)->head->next;
        free(p->data);
        free(p);
    }
    free(*list);
}

void print_reversed_int(TDoubleLinkedList *list)
{
    node *q=list->tail;
    while(q!=NULL)
    {
        printf("%d ",*(int *)(q->data));
        q=q->prev;
    }
    printf("\n");
}


//am considerat ca se doreste a se crea o lista crescatoare direct
void add_in_order(TDoubleLinkedList *list, void *data)
{
    node *p=list->head;
    node *new_node=(node *)malloc(sizeof(node));
    new_node->data=data;
    new_node->next=NULL;
    new_node->prev=NULL;
    if(p==NULL)
    {
        list->head=new_node;
        list->tail=new_node;
        list->len++;
    }
    else
    {
        while(p!=NULL&&(*(int*)p->data<*(int*)data))
            p=p->next;
        if(p==list->head)
        {
            new_node->next=list->head;
            new_node->prev=NULL;
            new_node->next->prev=new_node;
            list->head=new_node;
            list->len++;
            return;
        }
        if(p==NULL)
        {
            new_node->next=NULL;
            new_node->prev=list->tail;
            new_node->prev->next=new_node;
            list->tail=new_node;
            list->len++;
            return;
        }
        else
        {
            new_node->next=p;
            new_node->prev=p->prev;
            p->prev->next=new_node;
            p->prev=new_node;
            list->len++;
        }
    }
}

void sort_list_int(TDoubleLinkedList *list)
{
    node *pivot=list->head,*plimba;
    while(pivot->next!=NULL)
    {
        plimba=pivot->next;
        while(plimba!=NULL)
        {
            if(*(int *)plimba->data > *(int *)pivot->data)
            {
                int *aux=plimba->data;
                plimba->data=pivot->data;
                pivot->data=aux;
            }
            plimba=plimba->next;
        }
        pivot=pivot->next;
    }
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
        //scanf("%d",&poz);
        //ret=add(list,poz,val);
        add_in_order(list,val);
        print_int_list(list);
    }
    print_reversed_int(list);
    sort_list_int(list);
    print_int_list(list);
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&poz);
        ret=removenode(list,poz);
        print_int_list(list);
    }
    free_list(&list);
    return 0;
}