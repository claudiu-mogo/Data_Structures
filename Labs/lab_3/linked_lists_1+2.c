#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lista incepe de la pozitia 0
//a nu se introduce alt tip de data daca se cere numar

typedef struct node{
    void* data;
    struct node* next;
} node;

typedef struct TList {
    node* head;
    int len;
} TList;

int global_check=1;

void init(TList **list)
{
    *list=(TList *)malloc(sizeof(TList));
    (*list)->head=(node *)malloc(sizeof(node));
    (*list)->head->data=NULL;
    (*list)->len=0;
    (*list)->head->next=NULL;
    //(*list)->head=NULL;
}

int length(TList *list)
{
    int l=0;
    if(list->len==0)
        return l;
    node *p=list->head;
    while(p!=NULL)
    {
        l++;
        p=p->next;
    }
    return l;
}

void free_list(TList **list)
{
    node *p1;
    while((*list)->head!=NULL)
    {
        p1=(*list)->head;
        (*list)->head=(*list)->head->next;
        free(p1->data);
        free(p1);
    }
    free(*list);
}

int add(TList *list, int n, void* data)
{
    node *p=list->head;
    if(n<0||n>list->len)
    {
        return -1;
    }
    if(list->len==0)
    {
        list->head->data=data;
        list->len=1;
        return 1;
    }
    for(int i=0;i<n-1;i++)
        p=p->next;
    node* new_node;
    new_node=(node *)malloc(sizeof(node));
    new_node->next=NULL;
    new_node->data=data;
    if(n==0)
    {
        new_node->next=list->head;
        list->head=new_node;
    }
    else
    {
        new_node->next=p->next;
        p->next=new_node;
    }
    list->len=length(list);
    return 1;
}

node* removen(TList *list, int n)
{
    node *scos,*p=list->head;
    int i;
    if(list->len==0)
        return NULL;
    ///
    if(list->len==1 && n==0)
    {
        scos=list->head;
        list->head=NULL;
        list->len--;
        global_check=0;
        printf("Lista s-a golit\n");
        return scos;
    }
    ///
    if(n<0||n>list->len)
    {
        return NULL;
    }
    if(n==0)
    {
        scos=p;
        list->head=list->head->next;
        list->len--;
        return scos;
    }
    for(i=0;i<n-1;i++)
        p=p->next;
    scos=p->next;
    p->next=p->next->next;
    list->len--;
    return scos;
}

void print_int_list(TList *list)
{
    node *p=list->head;
    while(p!=NULL)
    {
        printf("%d ",*(int *)(p->data));
        p=p->next;
    }
    printf("\n");
}

void print_string_list(TList *list)
{
    node *p=list->head;
    while(p!=NULL)
    {
        printf("%s ",(char *)(p->data));
        //puts((char *)(p->data));
        p=p->next;
    }
    printf("\n");
}

void reverse_list(TList *list)
{
    node *p1,*p2,*p3=NULL;
    p1=NULL;
    p2=list->head;
    while(p2!=NULL)
    {
        p3=p2->next;
        p2->next=p1;
        p1=p2;
        p2=p3;
    }
    list->head=p1;
}

int main()
{
    int i,n,poz,*val,garbage,decizie,decizie1,ok=1;
    char *sir,buffer[20];
    TList *list1;
    node *separat;
    //scanf("%d",&n);
    //getchar();
    init(&list1);
    printf("Alege optiunea:\n1: intregi\n2: stringuri\n");
    scanf("%d",&decizie1);
    while(ok)
    {
        printf("Alege optiunea:\n1: add  2: remove  3: reverse  4: print  5: length  alt nr: exit\n");
        scanf("%d",&decizie);
        switch (decizie)
        {
            case 1:
            {
                if(decizie1==1)
                {
                    printf("Zi valoarea: ");
                    val=(int *)malloc(sizeof(int));
                    scanf("%d",val);
                    printf("Zi pozitia: ");
                    scanf("%d",&poz);
                    while(add(list1,poz,val)!=1)
                    {
                        printf("Not available. Zi pozitia: ");
                        scanf("%d",&poz);
                        //print_int_list(list1);
                    }
                }
                else
                {
                    printf("Zi sirul: ");
                    sir=(char *)malloc(20*sizeof(char));
                    getchar();
                    fgets(buffer,20,stdin);
                    buffer[strlen(buffer)-1]=buffer[strlen(buffer)];
                    strcpy(sir,buffer);
                    printf("Zi pozitia: ");
                    scanf("%d",&poz);
                    //getchar();
                    while(add(list1,poz,sir)!=1)
                    {
                        printf("Zi pozitia: ");
                        scanf("%d",&poz);
                        //getchar();
                    }
                }
                break;
            }
            case 2:
            {
                printf("Zi pozitia: ");
                scanf("%d",&poz);
                separat=removen(list1,poz);
                if(global_check==0)
                {
                    global_check=1;
                    free_list(&list1);
                    init(&list1);
                }
                if(separat==NULL)
                {
                    printf("Nu s-a scos nimic\n");
                }
                else
                {
                    free(separat->data);
                    free(separat);
                }
                break;
            }
            case 3:
            {
                if(list1->len<=0)
                {
                    printf("Nimic de inversat\n");
                    break;
                }
                reverse_list(list1);
                break;
            }
            case 4:
            {
                if(list1->len<=0)
                {
                    printf("Nimic de printat\n");
                    break;
                }
                printf("Lista actuala: ");
                if(decizie1==1)
                    print_int_list(list1);
                else
                    print_string_list(list1);
                break;
            }
            case 5:
            {
                printf("Lungimea sirului este: %d\n",length(list1));
                break;
            }
            default:
                ok=0;
            break;
        }
    }
    free_list(&list1);
    return 0;
}