#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Fisier asociat taskului 2.1.
Abordarea este de a adauga un camp e1_check in structura,
care sa decida daca un element va ramane in lista sau nu.
Nodurile vor ramane in lista pana la stabilirea eligibilitatii tuturor
*/

//functie pentru aflarea mediei aritmetice a k valori din lista,
//incepand de la pozitia start_poz
double average(DoubleLinkedList *list, int start_poz, int k)
{
    double sum=0;
    int i;
    node *p=list->head;
    //parcurgere pana la start_poz
    for(i=0;i<start_poz;i++)
        p=p->next;
    for(i=0;i<k;i++)
    {
        sum+=p->value;
        p=p->next;
    }
    return sum/k;
}

//calcularea deviatiei pentru o fereastra de k elemente,
//incepand de la start_poz
double deviation(DoubleLinkedList *list, int start_poz, int k)
{
    double av,sum=0;
    int i;
    av=average(list,start_poz,k);
    node *p=list->head;
    for(i=0;i<start_poz;i++)
        p=p->next;
    //aplicam formula propriu-zisa
    for(i=0;i<k;i++)
    {
        sum+=(p->value-av)*(p->value-av);
        p=p->next;
    }
    return sqrt(sum/k);
}

//functie care aduce lista in forma finala
//stabileste eligibilitatea fiecarui nod
//ii eliminam pe cei cu e1_check=0 (neeligibili)
void ex_e1(DoubleLinkedList *list, int *good_nodes,int k)
{
    int i,pozitie_de_scos,j;
    double dev,av,aux;
    node *p=list->head,*q;
    *good_nodes=list->len;
    //aplicam formulele pt fiecare fereastra
    for(i=0;i<=list->len-k;i++)
    {
        dev=deviation(list,i,k);
        av=average(list,i,k);
        q=p;
        for(j=0;j<k/2;j++)
            q=q->next;
        aux=q->value;
        //daca o valoare nu respecta conditia,
        //spunem ca nu este eligibil si actualizam e1_check si good_nodes
        if(aux<av-dev || aux>av+dev)
        {
            q->e1_check=0;
            (*good_nodes)--;
        }
        p=p->next;
    }
    p=list->head->next;
    pozitie_de_scos=2;
    //scoatem toate nodurile care nu au respectat conditia
    while(p!=list->tail->prev)
    {
        while(p->next->e1_check==0)
        {
            removenode(list,pozitie_de_scos);
        }
        pozitie_de_scos++;
        p=p->next;
    }
}