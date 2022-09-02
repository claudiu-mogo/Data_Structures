#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

/*
Strategia de lucru este de a muta, in functie de task, dupa cum urmeaza:
task1: input->matrice->arbore->vector->output
task2: input->vector->arbore->matrice->output
task3: input->matrice->arbore->arbore modificat->matrice->output
Perechile RGB din fisierele de tip .ppm au fost salvate intr-o matrice de char
Am ales aceasta abordare: 1. pt a fi mai usor si mai intuitiv de lucrat;
2. tipul char asigura dimensiunea de 1 byte (intuitiv de lucrat si de dat cast), 
iar culorile sunt maxim de 255, alt argument pt char
Toate mutarile pe baza arbolelui au fost DFS:
(radacina, top_left, top_right, bottom_right, bottom_left)
*/

//strcutura predefinita pt element din vector
typedef struct QuadtreeNode {
    unsigned char blue , green , red ;
    uint32_t area ;
    int32_t top_left, top_right ;
    int32_t bottom_left, bottom_right ;
} __attribute__ ( ( packed ) ) QuadtreeNode ;

//structura aferenta unui nod din arbore
//contine pointeri la copii, codurile de culori
//depth -> adancimea la care se afla nodul in arbore (radacina->0)
typedef struct Tree{
    struct Tree *tl, *tr, *bl, *br;
    unsigned char red,green,blue;
    int32_t depth;
}Tree;

//functie care aloca un nod dintr-un arbore
//si pune default copiii NULL
void init_tree(Tree **tree)
{
    *tree=(Tree *)malloc(sizeof(Tree));
    (*tree)->red=0;
    (*tree)->green=0;
    (*tree)->blue=0;
    (*tree)->depth=0;
    (*tree)->tl=NULL;
    (*tree)->tr=NULL;
    (*tree)->bl=NULL;
    (*tree)->br=NULL;
}

//functie care elibereaza recursiv un arbore
//se elibereaza de jos in sus
void rm_tree(Tree **tree)
{
    if((*tree)!=NULL)
    {
        rm_tree(&((*tree)->tl));
        rm_tree(&((*tree)->tr));
        rm_tree(&((*tree)->br));
        rm_tree(&((*tree)->bl));
        free((*tree));
    }
}

//functie care aloca si leaga un nod nou de tree
//tree va fi mereu parintele nodului nou
//poz determina ce copil vrem sa punem:
//1->top_left, 2->top_right, 3->bottom_right, 4->bottom_left
void insert(Tree *tree,int poz)
{
    Tree *node;
    init_tree(&node);
    node->depth=tree->depth+1;
    switch(poz)
    {
        case 1:
            tree->tl=node;
            break;
        case 2:
            tree->tr=node;
            break;
        case 3:
            tree->br=node;
            break;
        case 4:
            tree->bl=node;
            break;
        default:
            break;
    }
}

//color=0 ->red; 1->green; 2->blue
//calculeaza media pt una din culori dintr-un patrat de la x_start, y_start cu latura size
uint32_t average(int32_t x_start,int32_t y_start,char **mat,int8_t color,int32_t size)
{
    uint64_t sum=0;
    int32_t i,j;
    for(i=y_start;i<y_start+(size);i++)
    {
        for(j=x_start;j<x_start+(size);j++)
        {
            //parcurgem 3*j deoarece mereu avem calup de 3 culori
            //si sarim peste toate deodata
            //cast la unsigned char ca sa ramanem pe 0 255
            sum+=*(unsigned char*)(mat[i]+3*j+color);
        }
    }
    return (uint32_t) sum/(size*size);
}

//functie care aplica formula pt o zona incepand de la x_start, y_start
//total -> o dimensiune mare a imaginii intregi
//calculam latura (size-ul) zonei pe baza adancimii nodului din arbore
uint64_t mean(int32_t x_start,int32_t y_start,char **mat,int32_t depth,int32_t total)
{
    uint64_t size=total/(1<<depth),sum=0,i,j;
    //average-urile necesare pt formula
    uint32_t avg_red=average(x_start,y_start,mat,0,size);
    uint32_t avg_green=average(x_start,y_start,mat,1,size);
    uint32_t avg_blue=average(x_start,y_start,mat,2,size);
    //calculare suma de la numarator
    for(i=y_start;i<y_start+size;i++)
    {
        for(j=x_start;j<x_start+size;j++)
        {
            //cast la unsigned char ca sa ramanem pe 0 255
            sum+=(avg_red-*(unsigned char*)(mat[i]+3*j+0))
                    *(avg_red-*(unsigned char*)(mat[i]+3*j+0));
            sum+=(avg_green-*(unsigned char*)(mat[i]+3*j+1))
                    *(avg_green-*(unsigned char*)(mat[i]+3*j+1));
            sum+=(avg_blue-*(unsigned char*)(mat[i]+3*j+2))
                    *(avg_blue-*(unsigned char*)(mat[i]+3*j+2));
        }
    }
    //se intoarce rezultatul formulei
    return sum/(3*size*size);
}

//functie care muta datele din matricea de culori in arbore recursiv
//daca se respecta conditia, se aloca memorie pt nod
//si se construiesc copiii acestuia cu pozitii de start relative la cea a parintelui
//initial depth-ul radacinii este 0 si va creste pe masura ce construim
void complete_tree(Tree *tree,int32_t factor,int32_t x_start,int32_t y_start,
                                    char **mat,int32_t depth,int32_t total)
{
    //total = o dimensiune mare a imaginii intregi
    //se calculeaza latura zonei in functie de adancimea nodului in arbore
    uint64_t size=total/(1<<depth);
    //la nodul actual se atribuie culorile medii ale zonei
    tree->red=average(x_start,y_start,mat,0,size);
    tree->green=average(x_start,y_start,mat,1,size);
    tree->blue=average(x_start,y_start,mat,2,size);
    tree->depth=depth;
    //default copiii sunt NULL
    tree->bl=tree->br=tree->tl=tree->tr=NULL;
    //daca inca se mai poate diviza imaginea, inseram pe rand copiii
    if(tree!=NULL&&mean(x_start,y_start,mat,depth,total)>factor)
    {
        insert(tree,1);
        complete_tree(tree->tl,factor,x_start,y_start,mat,depth+1,total);
        insert(tree,2);
        complete_tree(tree->tr,factor,x_start+size/2,y_start,mat,depth+1,total);
        insert(tree,3);
        complete_tree(tree->br,factor,x_start+size/2,y_start+size/2,mat,depth+1,total);
        insert(tree,4);
        complete_tree(tree->bl,factor,x_start,y_start+size/2,mat,depth+1,total);
    }
}

//functie care numara frunzele recursiv
uint32_t count_leaves(Tree* tree)
{
    //daca nodul nu are bottom_left, atunci nu are niciun copil
    //deci este frunza
    if(tree->bl==NULL)
        return 1;
    return count_leaves(tree->tl)+count_leaves(tree->tr)+
            count_leaves(tree->br)+count_leaves(tree->bl);
}

//functie care numara nodurile recursiv
uint32_t count_nodes(Tree *tree)
{
    if(tree==NULL)
        return 0;
    return 1+count_nodes(tree->bl)+count_nodes(tree->br)+
            count_nodes(tree->tl)+count_nodes(tree->tr);
}

//functie care creeaza un vector din arborele tree; radacina va avea indice 0
//poz -> pozitia din vector pe care trebuie sa adaugam; total1 -> aria mare a imaginii
//Se parcurge DFS (radacina, top_left, top_right, bottom_right, bottom_left)
void generate_vector(Tree *tree,QuadtreeNode* vect,int poz,uint32_t total1)
{
    //daca exista informatie de mutat in vector
    if(tree!=NULL)
    {
        //mutam efectiv culorile la "structura" care incepe la poz
        (vect+poz)->blue=tree->blue;
        (vect+poz)->green=tree->green;
        (vect+poz)->red=tree->red;
        //calculam aria aferenta nodului curent, in functie de adancimea in tree
        (vect+poz)->area=total1/(1<<(tree->depth*2));
        //punem indicii copiilor ca fiind default -1 (nu modificam daca are copiii null)
        //nu o sa intre in if si raman -1
        (vect+poz)->bottom_left=(vect+poz)->bottom_right=-1;
        (vect+poz)->top_left=(vect+poz)->top_right=-1;
        //daca exista unul, exista toti copiii
        if(tree->tl)
        {
            //completam indicii copiilor sarind peste cate noduri se afla in subarborele
            //fiecarui copil anterior + 1 de la radacina (nodul curent)
            (vect+poz)->top_left=poz+1;
            (vect+poz)->top_right=poz+count_nodes(tree->tl)+1;
            (vect+poz)->bottom_right=poz+count_nodes(tree->tl)+count_nodes(tree->tr)+1;
            (vect+poz)->bottom_left=poz+count_nodes(tree->tl)
                            +count_nodes(tree->tr)+count_nodes(tree->br)+1;
        }
        //se genereaza vectorul DFS in continuare, dandu-se pozitia de start
        //pt poz se efectueaza aceleasi calcule ca mai devreme
        generate_vector(tree->tl,vect,poz+1,total1);
        generate_vector(tree->tr,vect,poz+count_nodes(tree->tl)+1,total1);
        generate_vector(tree->br,vect,poz+count_nodes(tree->tl)+count_nodes(tree->tr)+1,total1);
        generate_vector(tree->bl,vect,poz+count_nodes(tree->tl)
                            +count_nodes(tree->tr)+count_nodes(tree->br)+1,total1);
    }
}

//functie care parseaza inputul si lanseaza functiile necesare pt task1
//se salveaza RGB-urile din imaginea initiala intr-o matrice
void compress(FILE *f1, FILE *f2,int32_t factor)
{
    //citire din imagine datele initiale
    char useless_string[20],dimensions[20],*tk;
    int32_t height,width,maxval,i,j;
    fgets(useless_string,20,f1);
    fgets(dimensions,20,f1);
    tk=strtok(dimensions," \n");
    width=atoi(tk);
    tk=strtok(NULL," \n");
    height=atoi(tk);
    fgets(dimensions,20,f1);
    maxval=atoi(dimensions);
    /////////////
    //generare matrice din imagine
    //matricea va contine char-uri pt a fi clasic de tip byte
    //vom putea da cast-uri mai usor daca va fi nevoie
    char **mat;
    mat=(char **)malloc(height*sizeof(char *));
    for(i=0;i<height;i++)
        mat[i]=(char *)malloc(3*width*sizeof(char));
    for(i=0;i<height;i++)
    {
        fread(mat[i],width,3,f1);
    }
    //generare arbore din matrice, cu radacina initializata
    Tree *tree;
    init_tree(&tree);
    complete_tree(tree,factor,0,0,mat,0,width);
    //din arbore in vector acum
    QuadtreeNode* vect=malloc(count_nodes(tree)*sizeof(QuadtreeNode));
    generate_vector(tree,vect,0,height*width);
    //afisare in fisier de output
    uint32_t leaves=(count_leaves(tree)),nodes=count_nodes(tree);
    fwrite(&leaves,sizeof(uint32_t),1,f2);
    fwrite(&nodes,sizeof(uint32_t),1,f2);
    fwrite(vect,sizeof(QuadtreeNode),nodes,f2);
    //eliberare memorie pt vector, arbore si matrice
    free(vect);
    rm_tree(&tree);
    for(i=0;i<height;i++)
        free(mat[i]);
    free(mat);
}

//functie care genereaza arborele din vectorul de compresie
//poz -> pozitia din vector de unde luam datele
//generam arborele tot DFS
void move_to_tree(Tree *tree,QuadtreeNode* vect,int32_t poz,int32_t depth)
{
    //punere culori si adancime in nod
    tree->red=(vect+poz)->red;
    tree->green=(vect+poz)->green;
    tree->blue=(vect+poz)->blue;
    tree->depth=depth;
    //daca nodul mai are un copil (adica pe toti)
    if((vect+poz)->top_left!=-1)
    {
        //initializare si punere in arbore recursiv
        insert(tree,1);
        move_to_tree(tree->tl,vect,(vect+poz)->top_left,depth+1);
        insert(tree,2);
        move_to_tree(tree->tr,vect,(vect+poz)->top_right,depth+1);
        insert(tree,3);
        move_to_tree(tree->br,vect,(vect+poz)->bottom_right,depth+1);
        insert(tree,4);
        move_to_tree(tree->bl,vect,(vect+poz)->bottom_left,depth+1);
    }
}

//functie care transpune arborele in matricea de RGB-uri ("imaginea propriu-zisa")
//facem porcesul invers fata de functiile anterioare
//total -> o dimensiune a matricei mari
void move_to_mat(Tree *tree, char **mat,int32_t x_start,int32_t y_start,int32_t total)
{
    //latura patratului actual este calculata relativ cu adancimea nodului din arbore
    uint64_t size=total/(1<<tree->depth),i,j;
    //ne intereseaza doar culorile frunzelor
    if(tree->tl==NULL)
    {
        //construim matrice din coltul stanga sus, pe linii
        for(i=y_start;i<y_start+size;i++)
        {
            for(j=x_start;j<x_start+size;j++)
            {
                //punem valorile in matrice
                //mat este de char-uri, merge fara cast
                *(mat[i]+3*j+0)=tree->red;
                *(mat[i]+3*j+1)=tree->green;
                *(mat[i]+3*j+2)=tree->blue;
            }
        }
    }
    else
    {
        //punem recursiv DFS copiii in matrice
        move_to_mat(tree->tl,mat,x_start,y_start,total);
        move_to_mat(tree->tr,mat,x_start+size/2,y_start,total);
        move_to_mat(tree->br,mat,x_start+size/2,y_start+size/2,total);
        move_to_mat(tree->bl,mat,x_start,y_start+size/2,total);
    }
}

//functie de scriere in fisier a matricei
void write_image(FILE *f2,int32_t height,int32_t width,char **mat)
{
    int i;
    char useless_string[20],dimensions[20],width1[20],height1[20];
    //completare antet .ppm
    strcpy(useless_string,"P6\n");
    sprintf(width1,"%d",width);
    sprintf(height1,"%d",height);
    strcpy(dimensions,width1);
    strcat(dimensions," ");
    strcat(dimensions,height1);
    strcat(dimensions,"\n");
    //scriere in binar a antetului
    fwrite(useless_string,strlen(useless_string)*sizeof(char),1,f2);
    fwrite(dimensions,strlen(dimensions)*sizeof(char),1,f2);
    strcpy(useless_string,"255\n");
    fwrite(useless_string,strlen(useless_string)*sizeof(char),1,f2);
    //scriere in binar a matricei de RGB
    //3*sizeof(char) -> fiecare culoare are cate un byte
    for(i=0;i<height;i++)
        fwrite(mat[i],3*sizeof(char),width,f2);
}

//functie care citeste datele si lanseaza in executie task2
void decompress(FILE *f1, FILE *f2)
{
    //citire din binar in vector
    uint32_t leaves,nodes;
    fread(&leaves,sizeof(uint32_t),1,f1);
    fread(&nodes,sizeof(uint32_t),1,f1);
    //alocare si citire vector de structuri
    QuadtreeNode* vect=(QuadtreeNode*)malloc(nodes*sizeof(QuadtreeNode));
    fread(vect,sizeof(QuadtreeNode),nodes,f1);
    //din vector in arbore
    //mereu vom avea radacina, o alocam de acum
    Tree *tree;
    init_tree(&tree);
    move_to_tree(tree,vect,0,0);
    //din arbore in matricea de pixeli
    char **mat;
    int32_t height,width,i;
    //vect->area va avea area radacinii, deci a intregii imagini
    height=width=(sqrt(vect->area));
    mat=(char **)malloc(height*sizeof(char *));
    for(i=0;i<height;i++)
        mat[i]=(char *)malloc(3*width*sizeof(char));
    move_to_mat(tree,mat,0,0,width);
    //afisare
    write_image(f2,height,width,mat);
    //eliberare memorie
    free(vect);
    rm_tree(&tree);
    for(i=0;i<height;i++)
        free(mat[i]);
    free(mat);
}

//functie de swap pointeri la nod de arbore
void basic_swap(Tree **a, Tree **b)
{
    Tree *aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

//pt a roti orizontal trebuie sa interschimam recursiv stanga cu dreapta
//radacina nu are rost sa fie schimbata, asa ca ne uitam la copii
void horizontally(Tree *tree)
{
    //daca are sens schimbarea + punct fix
    if(tree->tl!=NULL)
    {
        basic_swap(&tree->tl,&tree->tr);
        basic_swap(&tree->bl,&tree->br);
        //schimbare copii
        horizontally(tree->tl);
        horizontally(tree->tr);
        horizontally(tree->br);
        horizontally(tree->bl);
    }
}

//functie care roteste arborele cu totul
//adica top_left cu bottom_right si bottom_left cu top_right
//ca si cum am citi imaginea de jos si de la dreapta la stanga
void completely(Tree *tree)
{
    if(tree->tl!=NULL)
    {
        basic_swap(&tree->tl,&tree->br);
        basic_swap(&tree->bl,&tree->tr);
        completely(tree->tl);
        completely(tree->tr);
        completely(tree->br);
        completely(tree->bl);
    }
}

//functie aferenta task-ului 3
//care primeste factorul de oprire si tipul rotirii
void mirror(FILE *f1, FILE *f2,int32_t factor,int8_t type)
{
    char useless_string[20],dimensions[20],*tk;
    int32_t height,width,maxval,i,j;
    //citire imagine
    fgets(useless_string,20,f1);
    fgets(dimensions,20,f1);
    tk=strtok(dimensions," \n");
    width=atoi(tk);
    tk=strtok(NULL," \n");
    height=atoi(tk);
    fgets(dimensions,20,f1);
    maxval=atoi(dimensions);
    //generare matrice din imagine
    char **mat;
    mat=(char **)malloc(height*sizeof(char *));
    for(i=0;i<height;i++)
        mat[i]=(char *)malloc(3*width*sizeof(char));
    //citire efectiva RGB
    for(i=0;i<height;i++)
    {
        fread(mat[i],width,3,f1);
    }
    //completare arbore ca la task1
    Tree *tree;
    init_tree(&tree);
    complete_tree(tree,factor,0,0,mat,0,width);
    //rotiri de arbori in functie de tip
    //pt rotirea verticala intai facem intoarcere completa a arborelui
    //pt orizontala lansam doar functia de orizontal
    if(type==2)
        completely(tree);
    horizontally(tree);
    //din arbore in matricea de afisat
    move_to_mat(tree,mat,0,0,width);
    //afisare
    write_image(f2,height,width,mat);
    //eliberare memorie
    rm_tree(&tree);
    for(i=0;i<height;i++)
        free(mat[i]);
    free(mat);
}

int main(int argc, char** argv)
{
    int nr_arg=0;
    //sa stim peste cate argumente trebuie sa sarim
    if(!strcmp(argv[1],"-c"))
        nr_arg=3;
    else if(!strcmp(argv[1],"-m"))
        nr_arg=4;
    else
        nr_arg=2;
    //deschidere fisiere
    FILE *f1=fopen(argv[nr_arg++],"rb");
    FILE *f2=fopen(argv[nr_arg],"wb");
    if(!strcmp(argv[1],"-c"))
    {
        //citire factor si lansare functie de compress
        int32_t factor=atoi(argv[2]);
        compress(f1,f2,factor);
    }
    else if(!strcmp(argv[1],"-m"))
    {
        //citire factor si tipul rotirii
        int32_t factor=atoi(argv[3]);
        int8_t type;
        //orizontal -> type=1
        //vertical -> type=2
        if(!strcmp(argv[2],"h"))
            type=1;
        else
            type=2;
        mirror(f1,f2,factor,type);
    }
    else
    {
        //task2
        decompress(f1,f2);
    }
    //inchidere fisiere
    //eliberarea de memorie se face in functii
    fclose(f1); fclose(f2);
    return 0;
}