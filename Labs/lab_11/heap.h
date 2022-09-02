typedef struct heapnode {
    int index;
    int val;
    struct heapnode *left, *right,*parent;
} heapnode;

typedef struct Heap {
    int no_heapnodes;
    struct heapnode *root;
} Heap;

void init(Heap **h);
void dec_to_bin(int n, char *s);
void to_up(Heap *h,heapnode *p);
void insert(Heap *h,int val,int index);
void heapify(heapnode *p);
int remove_root(Heap *h);
void search_pre_order(heapnode *h,int index,int new_dist);
