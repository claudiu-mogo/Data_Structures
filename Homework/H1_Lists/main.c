#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "all_tasks.h"

/*
Functia main care preia datele din linia de comanda
si lanseaza in executie cerintele 
*/

//argc->nr de argumente
//argv->vector de "cuvinte" (argumentele propriu-zise)
int main(int argc, char **argv)
{
    int i,nrelem,tmst,good_nodes,punct2,delta,stat=0;
    double val;
    //cream si initializam lista
    DoubleLinkedList *list;
    init(&list);
    scanf("%d",&nrelem);
    //good_nodes reprezinta nr de elemente din lista finala
    //(pe care vrem sa o afisam dupa modificari)
    good_nodes=nrelem;
    //citire date
    for(i=0;i<nrelem;i++)
    {
        scanf("%d%lf",&tmst,&val);
        add_at_end(list,tmst,val);
    }
    //parcurgem fiecare argument in ordine
    for(i=1;i<argc;i++)
    {
        //lansare in executie a unei functii conform cu argumentul
        if(!(strcmp(argv[i],"--e1")))
            ex_e1(list,&good_nodes,5);
        if(!(strcmp(argv[i],"--e2")))
        {
            punct2=1;
            filtrare_med(list,5,&good_nodes,punct2);
        }
        if(!(strcmp(argv[i],"--e3")))
        {
            punct2=2;
            filtrare_med(list,5,&good_nodes,punct2);
        }
        if(argv[i][2]=='u')
            uniformizare(list);
        if(argv[i][2]=='s')
        {
            stat=1;
            //parsare argument - aflare delta
            delta=atoi(argv[i]+4);
            statistici(list,delta);
        }
        if(argv[i][2]=='c')
        {
            completare(list,3);
            good_nodes=list->len;
        }

    }
    //stat reprezinta o conditie asociata taskului 2.5 (statistici)
    //la acest task nu vrem sa afisam lista
    if(!stat)
        print_list(list,good_nodes);
    //eliberare memorie
    free_list(&list);
    return 0;
}