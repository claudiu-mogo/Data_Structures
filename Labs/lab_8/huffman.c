#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//am copiat si adaptat functiile din celalalt fisier pt cerinta noua

typedef struct HuffNode {
    char ch; // caracterul, daca nodul e frunza, altfel ch = 0
    int val,rad; // frecventa
    struct HuffNode *left, *right,*parent;
} HuffNode;

typedef struct node {
    struct HuffNode *node;
    struct node *left, *right,*parent;
} node;

typedef struct Heap {
    int no_nodes;
    struct node *root;
} Heap;

void init_heap(Heap **h)
{
    (*h)=malloc(sizeof(Heap));
    (*h)->root=NULL;
    (*h)->no_nodes=0;
}

void dec_to_bin(int n, char *s)
{
    int i;
    for(i=0;i<8;i++)
        s[i]='0';
    while(n)
    {
        s[--i]=n%2+'0';
        n/=2;
    }
    s[8]='\0';
}

void to_up(Heap *h,node *p)
{
    if(p!=h->root&&p->node->val<=p->parent->node->val)
    {
        int aux=p->node->val;
        p->node->val=p->parent->node->val;
        p->parent->node->val=aux;
        aux=p->node->rad;
        p->node->rad=p->parent->node->rad;
        p->parent->node->rad=aux;
        char aux2=p->node->ch;
        p->node->ch=p->parent->node->ch;
        p->parent->node->ch=aux2;
        to_up(h,p->parent);
    }
}

void insert_heap(Heap *h,node *n)
{
    if(h->root==NULL)
    {
        //h->root=malloc(sizeof(node));
        h->no_nodes=1;
        h->root=n;
        /*
        h->root->node=malloc(sizeof(HuffNode));
        h->root->node->val=val;
        h->root->node->ch=ch;*/
        h->root->left=h->root->right=h->root->parent=NULL;
        return;
    }
    h->no_nodes++;
    char sir[9];
    dec_to_bin(h->no_nodes,sir);
    int i=0;
    node *p=h->root;
    while(sir[i]!='1')
    {
        i++;
    }
    i++;
    while(i<7)
    {
        if(sir[i]=='0')
            p=p->left;
        else
            p=p->right;
        i++;
    }
    if(sir[i]=='0')
    {
        //p->left=malloc(sizeof(node));
        p->left=n;
        /*
        p->left->node=malloc(sizeof(HuffNode));
        p->left->node->val=val;
        p->left->node->ch=ch;*/
        p->left->parent=p;
        p->left->left=p->left->right=NULL; 
        to_up(h,p->left);
    }
    else
    {
        //p->right=malloc(sizeof(node));
        p->right=n;
        /*
        p->right->node=malloc(sizeof(HuffNode));
        p->right->node->val=val;
        p->right->node->ch=ch; */
        p->right->parent=p;
        p->right->left=p->right->right=NULL;
        to_up(h,p->right);
    }
}

void heapify(node *p)
{
    if(p==NULL)
        return;
    int smallest_son=10000,l=0,r=0;
    if(p->left!=NULL&&p->left->node->val<=smallest_son)
    {
        smallest_son=p->left->node->val;
        l=1;
    }
    if(p->right!=NULL&&p->right->node->val<=smallest_son)
    {
        smallest_son=p->right->node->val;
        r=1;
    }
    if(r==1&&p->right->node->val<p->node->val)
    {
        int aux=p->right->node->val;
        p->right->node->val=p->node->val;
        p->node->val=aux;
        char aux2=p->right->node->ch;
        p->right->node->ch=p->node->ch;
        p->node->ch=aux2;
        heapify(p->right);
    }
    else if(l==1&&p->left->node->val<p->node->val)
    {
        int aux=p->left->node->val;
        p->left->node->val=p->node->val;
        p->node->val=aux;
        char aux2=p->left->node->ch;
        p->left->node->ch=p->node->ch;
        p->node->ch=aux2;
        heapify(p->left);
    }
}

node* remove_root(Heap *h)
{
    if(h->root==NULL)
        return NULL;
    char sir[9];
    dec_to_bin(h->no_nodes,sir);
    int i=0,val_rem;
    char c_rem;
    node *p=h->root,*ret;
    while(sir[i]!='1')
    {
        i++;
    }
    i++;
    while(i<7)
    {
        if(sir[i]=='0')
            p=p->left;
        else
            p=p->right;
        i++;
    }
    if(sir[i]=='0')
    {
        val_rem=h->root->node->val;
        h->root->node->val=p->left->node->val;
        p->left->node->val=val_rem;
        c_rem=h->root->node->ch;
        h->root->node->ch=p->left->node->ch;
        p->left->node->ch=c_rem;
        ret=p->left;
        p->left=NULL;
    }
    else
    {
        val_rem=h->root->node->val;
        h->root->node->val=p->right->node->val;
        p->right->node->val=val_rem;
        c_rem=h->root->node->ch;
        h->root->node->ch=p->right->node->ch;
        p->right->node->ch=c_rem;
        ret=p->right;
        p->right=NULL;
    }
    heapify(h->root);
    h->no_nodes--;
    return ret;
}

//pt arbore

void init(HuffNode **tree)
{
    *tree=(HuffNode *)malloc(sizeof(HuffNode));
    (*tree)->val=0;
    (*tree)->rad=0;
    (*tree)->ch=0;
    (*tree)->parent=NULL;
    (*tree)->left=NULL;
    (*tree)->right=NULL;
}

int height(HuffNode *tree)
{
    int h1=0,h2=0;
    if(tree==NULL)
        return -1;
    h1=height(tree->left);
    h2=height(tree->right);
    if(h1>h2)
        return 1+h1;
    return 1+h2;
}

void print_pre_order(node *n)
{
    if(n!=NULL)
    {
        printf("%c %d\n",n->node->ch,n->node->val);
        print_pre_order(n->left);
        print_pre_order(n->right);
    }
}

void print_huff(HuffNode *n)
{
    if(n!=NULL)
    {
        printf("%c %d\n",n->ch,n->val);
        print_huff(n->left);
        print_huff(n->right);
    }
}

void printArray(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}

void printHCodes(HuffNode *root, int arr[], int top) {
  if (root->left) 
  {
    arr[top] = 0;
    printHCodes(root->left, arr, top + 1);
  }
  if (root->right) 
  {
    arr[top] = 1;
    printHCodes(root->right, arr, top + 1);
  }
  if (root->left==NULL&&root->right==NULL) 
  {
    printf("%c| ", root->ch);
    printArray(arr, top);
  }
}

int main()
{
    HuffNode *tree;
    init(&tree);
    Heap *h;
    init_heap(&h);
    FILE *f1;
    f1=fopen("huff.in","r");
    node *citit;
    int nr_elem,freq,i;
    char c,buffer[50],cuvant[50];
    fgets(buffer,50,f1);
    sscanf(buffer,"%d",&nr_elem);
    //fscanf(f1,"%d",&nr_elem);
    //fgetc(f1);
    printf("%d\n",nr_elem);
    for(i=0;i<nr_elem;i++)
    {
        fgets(buffer,50,f1);
        sscanf(buffer,"%c%d",&c,&freq);
        //fscanf(f1,"%c%d",&c,&freq);
        //fgetc(f1);
        printf("%d\n",freq);
        citit=malloc(sizeof(node));
        citit->node=malloc(sizeof(HuffNode));
        citit->node->left=citit->node->right=NULL;
        citit->node->val=freq;
        citit->node->ch=c;
        insert_heap(h,citit);
    }
    print_pre_order(h->root);
    printf("------------------------\n");
    node *save1, *save2,*top1;
    HuffNode *top;
    while(h->no_nodes!=2)
    {
        save1=remove_root(h);
        save2=remove_root(h);
        init(&top);
        top->ch='#';
        top->val=save1->node->val+save2->node->val;
        top->left=save1->node;
        top->right=save2->node;
        top1=malloc(sizeof(node));
        top1->node=top;
        insert_heap(h,top1);
        print_pre_order(h->root);
        printf("------------------------\n");
    }
    save1=remove_root(h);
    print_pre_order(h->root);
    printf("------------------------\n");
    //print_pre_order(h->root);
    init(&top);
    top->ch='#';
    top->val=save1->node->val+h->root->node->val;
    top->left=save1->node;
    top->right=h->root->node;
    top1=malloc(sizeof(node));
    top1->node=top;
    //print_huff(top);
    insert_heap(h,top1);
    print_pre_order(h->root);
    printf("------------------------\n");
    //ramanem in arbore cu 2 noduri si trebuie sa vedem care dintre
    //ele este copilul
    //radacina heapului macum este doar ajutatoare
    //print_huff(h->root->node);
    if(h->root->left)
    {
        print_huff(h->root->left->node);
    }
    else
        print_huff(h->root->right->node);
    int cod[300];
    printHCodes(h->root->left->node,cod,0);
    fgets(cuvant,50,stdin);
    int pozcurr=0;
    fclose(f1);
    return 0;
}