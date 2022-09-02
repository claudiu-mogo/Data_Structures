#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Calup de functii pentru rezolvarea task-ului 2.2. in intregime.
Abordarea este de a crea o lista auxiliara cu timestampurile si valorile bune
La final mutam toata lista auxiliara in cea initiala
si eliberam memoria pt aux
presupunand k impar, in lista finala vor fi mereu cu k-1 mai putine elemente
*/

//functie pt sortarea listei
//consideram un pivot care sta pe loc si in care aducem cel mai mic
//element de la pozitia pivotului pana la final
void sort_list(DoubleLinkedList *list)
{
    node *pivot=list->head,*plimba;
    while(pivot->next!=NULL)
    {
        //parcurgem de la urmatorul element pana la final
        plimba=pivot->next;
        while(plimba!=NULL)
        {
            if(plimba->value < pivot->value)
            {
                double aux=plimba->value;
                plimba->value=pivot->value;
                pivot->value=aux;
            }
            plimba=plimba->next;
        }
        pivot=pivot->next;
    }
}

//functie pt aflarea valorii mediane
//punem k elemente intr-o lista auxiliara, pe care o sortam
//valoarea mediana este reprezentata de valoare din mijloc
double mediana(DoubleLinkedList *list,int start_poz,int k)
{
    int i,j;
    double average_val;
    //creare lista auxiliara
    DoubleLinkedList *aux_list;
    init(&aux_list);
    node *p=list->head,*q;
    //ajungem la pozitia de start a ferestrei
    for(i=0;i<start_poz;i++)
    {
        p=p->next;
    }
    //salvam pozitia de start a ferestrei
    q=p;
    for(j=0;j<k/2;j++)
        q=q->next;
    for(i=0;i<k;i++)
    {
        //adaugam elemente in lista auxiliara,
        //toate cu timestamp-ul elementului din mijlocul ferestrei
        add_at_end(aux_list,q->timestamp,p->value);
        p=p->next;
    }
    //sortam lista si luam valoarea din mijloc
    sort_list(aux_list);
    q=aux_list->head;
    for(j=0;j<k/2;j++)
        q=q->next;
    average_val=q->value;
    //eliberare lista
    free_list(&aux_list);
    return average_val;
}

//functia comuna e2 si e3, punct==1 -> e2; punct==2 -> e1
//se creeaza o lista auxiliara cu velorile calculate prin mediana sau average
void filtrare_med(DoubleLinkedList *list,int k,int *good_nodes,int punct)
{
    node *p=list->head,*q;
    int i,j;
    double average_val;
    //creare aux_list cu valorile noi
    DoubleLinkedList *aux_list;
    init(&aux_list);
    for(i=0;i<=list->len-k;i++)
    {
        if(punct==1)
            average_val=mediana(list,i,k);
        else
            average_val=average(list,i,k);
        q=p;
        for(j=0;j<k/2;j++)
            q=q->next;
        add_at_end(aux_list,q->timestamp,average_val);
        p=p->next;
    }
    //mereu vom avea cu k-1 mai putine elemente in lista decat la inceput
    //stergem k-1 elemente si actualizam nr de noduri 
    for(i=0;i<k-1;i++)
    {
        removenode(list,0);
        (*good_nodes)--;
    }
    //mutare date din aux_list in lista initiala
    p=list->head;
    q=aux_list->head;
    for(i=0;i<list->len;i++)
    {
        p->e1_check=q->e1_check;
        p->timestamp=q->timestamp;
        p->value=q->value;
        p=p->next;
        q=q->next;
    }
    //eliberare memorie lista
    free_list(&aux_list);
}