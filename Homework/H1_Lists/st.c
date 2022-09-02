#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Strategia de lucru este de a afla un multiplier intreg,
cel mai mare nr, care inmultit cu delta sa fie mai mic decat
orice valoare.
Pentru aceasta sortam lista. Tot lista sortata ne va ajuta
si la aflarea intervalelor si a numarului de elemente din acestea. 
*/

void statistici(DoubleLinkedList *list, int delta)
{
    int multipl,count;
    double rez;
    //sortam lista
    sort_list(list);
    node *p=list->head;
    //punem in multiplier nr cu care vrem sa inmultim
    //pt a obtine capatul inferior al intervalului cu cele mai mici nr
    rez=p->value/delta;
    if(rez>=0)
        multipl=(int)rez;
    else
        multipl=(int)rez-1;
    //parcurgere lista
    while(p!=NULL)
    {
        count=0;
        //conditie de siguranta
        while(p!=NULL&&p->value<(double)multipl*delta)
            multipl++;
        //parcurgem lista pana dam de un nr care nu mai este in interval
        while(p!=NULL&&p->value>=multipl*delta&&p->value<=(multipl+1)*delta)
        {
            count++;
            p=p->next;
        }
        //afisare interval si nr de elemente
        if(count)
        {
            printf("[%d, %d] %d\n",multipl*delta,(multipl+1)*delta,count);
        }
        else
        {
            if(p!=NULL)
                p=p->next;
        }
        //dupa ce am terminat un interval, aflam capatul superior urmator
        //urmatorul element pt care trebuie interval va fi p->value
        while(p!=NULL&&p->value>(double)(multipl+1)*delta)
            multipl++;
    }
}