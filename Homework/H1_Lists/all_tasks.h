/*
Header asociat tuturor functiilor.
Declaram 2 structurii prin care generam lista dublu inlantuita.
*/

//structura unui nod. e1_check ne ajuta sa decidem eligibilitatea
//de a ramane in lista dupa verificarea de la e1.
//timestamp si value reprezinta datele primite ca input. 
typedef struct node{
    int timestamp;
    double value;
    struct node *next;
    struct node *prev;
    int e1_check;
} node;

//structura listei propriu-zise
typedef struct {
    node *head;
    node *tail;
    int len;
} DoubleLinkedList;

//operatiile basic cu liste
void init(DoubleLinkedList **list);
void free_list(DoubleLinkedList **list);
void add_at_end(DoubleLinkedList *list, int timest, double data);
void add_middle(DoubleLinkedList *list, int n, int timest, double data);
void removenode(DoubleLinkedList *list, int n);
//functiile asociate cerintelor
double average(DoubleLinkedList *list, int start_poz, int k);
double deviation(DoubleLinkedList *list, int start_poz, int k);
void sort_list(DoubleLinkedList *list);
void print_list(DoubleLinkedList *list,int good_nodes);
double mediana(DoubleLinkedList *list,int start_poz,int k);
void ex_e1(DoubleLinkedList *list, int *good_nodes,int k);
void filtrare_med(DoubleLinkedList *list,int k,int *good_nodes,int punct);
void uniformizare(DoubleLinkedList *list);
double omega(int i, int k);
double func(DoubleLinkedList *list, int times, int k, node *l, node *r);
void completare(DoubleLinkedList *list, int k);
void statistici(DoubleLinkedList *list, int delta);