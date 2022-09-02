typedef struct heapnode {
    int index;
    float val;
    struct heapnode *left, *right,*parent;
} heapnode;

typedef struct Heap {
    int no_heapnodes;
    struct heapnode *root;
} Heap;

void init(Heap **h);
void dec_to_bin(int n, char *s);
void to_up(Heap *h,heapnode *p);
void insert(Heap *h,float val,int index);
void heapify(heapnode *p);
int remove_root(Heap *h);
