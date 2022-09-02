#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

//se initializeaza lista: alocare memorie + lungime=0
void init(DoubleLinkedList **list)
{
    *list=(DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    (*list)->head=NULL;
    (*list)->tail=NULL;
    (*list)->len=0;
}

//eliberare memorie lista
void free_list(DoubleLinkedList **list)
{
    node *p;
    //se parcurge fiecare nod in parte si eliberare nod
    while((*list)->head!=NULL)
    {
        p=(*list)->head;
        (*list)->head=(*list)->head->next;
        free(p);
    }
    //eliberare memorie lista
    free(*list);
}

//functie de adaugare elemente la finalul listei
void add_at_end(DoubleLinkedList *list, int timest, double data)
{
    //alocare si "initializare" nod nou
    node *new_node=(node *)malloc(sizeof(node));
    new_node->timestamp=timest;
    new_node->value=data;
    new_node->e1_check=1;
    new_node->next=NULL;
    new_node->prev=NULL;
    //daca lista este goala
    if(list->len==0)
    {
        list->head=new_node;
        list->tail=new_node;
        list->len++;
        return ;
    }
    //daca lista are cel putin un element
    new_node->prev=list->tail;
    list->tail->next=new_node;
    list->tail=new_node;
    list->len++;
}

//adaugare elemente la o pozitie random in lista
//pentru eficienta, verificam daca pozitia pe care vrem sa adaugam se afla
//mai aproape de head sau mai aproape de tail.
//incrementam lungimea listei
void add_middle(DoubleLinkedList *list, int n, int timest, double data)
{
    //alocare si "initializare" nod nou
    node *new_node=(node *)malloc(sizeof(node));
    new_node->timestamp=timest;
    new_node->value=data;
    new_node->e1_check=1;
    new_node->next=NULL;
    new_node->prev=NULL;
    //daca pozitia este mai aproape de head - parcurgere  -->
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
        //daca pozitia este mai aproape de tail - parcurgere  <--
        node *p=list->tail;
        for(int i=list->len-1;i>n-1;i--)
            p=p->prev;
        new_node->next=p->next;
        new_node->prev=p;
        p->next->prev=new_node;
        p->next=new_node;
        list->len++;
    }
}

//functie care scoate si elibereaza memoria pt nodul aflat pe pozitia n
//abordam toate cazurile posibile
//Scadem lungimea listei
void removenode(DoubleLinkedList *list, int n)
{
    //daca vrem sa eliberam head-ul
    if(n==0)
    {
        node *q=list->head;
        list->head=list->head->next;
        list->head->prev=NULL;
        free(q);
        list->len--;
        return ;
    }
    //daca vrem sa eliberam tail-ul
    if(n==list->len-1)
    {
        node *p=list->tail;
        list->tail=list->tail->prev;
        list->tail->next=NULL;
        free(p);
        list->len--;
        return ;
    }
    //vrem sa dam "remove" de pe o pozitie random
    //vedem daca n este mai aproape de head sau de tail
    if(n<list->len/2)
    {
        node *p=list->head;
        for(int i=0;i<n-1;i++)
            p=p->next;
        node *q=p->next;
        p->next=p->next->next;
        p->next->prev=p;
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
        free(q);
        list->len--;
    }
}

//afisare lista
void print_list(DoubleLinkedList *list,int good_nodes)
{
    //afisare nr de elemente
    printf("%d\n",good_nodes);
    node *p=list->head;
    while(p!=NULL)
    {
        //afisare lista cu valori cu 2 zecimale rotunjite
        printf("%d %.2lf\n",p->timestamp,p->value);
        p=p->next;
    }
}