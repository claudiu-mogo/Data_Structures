#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Fisier care duce la rezolvarea taskului 2.4.
Functiile omega si func functioneaza pentru i si k oarecare.
In locul listelor left si right vom avea 2 pointeri l si r,
care pointeaza spre grupurile de noduri asociate lui left si right
*/

//functie care calculeaza omega (sau w) dupa formula
double omega(int i, int k)
{
    double sum=0,rez=0;
    int j;
    for(j=0;j<k;j++)
    {
        sum+=(double)j/(k-1)*j/(k-1)*0.9+0.1;
    }
    rez=(double)i/(k-1)*i/(k-1)*0.9+0.1;
    return rez/sum;
}

//Functie care calculeaza valoarea lui f pentru ferestre de dimensiune k
//l si r reprezinta momentan vecinii gap-ului,
//o sa ii aducem pe acestia la echivalentul lui right[0] si left[0]
//times == timestamp-ul pe care vrem sa il adaugam
double func(DoubleLinkedList *list, int times,int k,node *l,node *r)
{
    int i;
    double C,sum1=0,sum2=0;
    //calculam C dupa formula
    C=1.0*(times-l->timestamp)/(r->timestamp-l->timestamp);
    //facem ca l sa pointeze la echivalentul lui left[0]
    for(i=0;i<k-1;i++)
        l=l->prev;
    //facem ca r sa pointeze la echivalentul lui right[0]
    for(i=0;i<k-1;i++)
        r=r->next;
    for(i=0;i<k;i++)
    {
        sum1+=l->value*omega(i,k);
        l=l->next;
    }
    for(i=0;i<k;i++)
    {
        sum2+=r->value*omega(i,k);
        r=r->prev;
    }
    //intoarcem valoarea functiei, conform formula 
    return ((1-C)*sum1+C*sum2);
}

//functia principala, care adauga elementele utile in lista
void completare(DoubleLinkedList *list, int k)
{
    node *p=list->head,*l,*r;
    int i=0,new_time,de_ajuns;
    while(p->next!=NULL)
    {
        //de_ajuns == timestamp-ul urmator gap-ului
        de_ajuns=p->next->timestamp;
        if(de_ajuns-p->timestamp>1000)
        {
            //setam l si r sa pointeze la vecini momentan, in func ajung la 0
            //l si r raman la fel pana se umple gap-ul
            l=p;
            r=p->next;
            //new_time este constant timpul pe care vrem sa il adaugam
            new_time=p->timestamp+200;
            while(new_time<de_ajuns)
            {
                add_middle(list,i+1,new_time,func(list,new_time,k,l,r));
                p=p->next;
                i++;
                new_time=p->timestamp+200;
            }
        }
        p=p->next;
        i++;
    }
}