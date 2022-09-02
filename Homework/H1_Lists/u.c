#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Functie atribuita taskului 2.3
Se verifica apartenenta la intervalul [100,1000]
Se aplica modificarile necesare daca diferenta este corespunzatoare
*/

void uniformizare(DoubleLinkedList *list)
{
    node *p=list->head->next;
    double dif;
    while(p!=NULL)
    {
        dif=p->timestamp - p->prev->timestamp;
        if(dif<0)
            dif=(-1)*dif;
        //verificare apartenenta interval
        if(dif>=100 && dif<=1000)
        {
            //modificare cu valori medii
            p->timestamp=(p->timestamp+p->prev->timestamp)/2;
            p->value=(p->value+p->prev->value)/2;
        }
        p=p->next;
    }
}