#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTree {
    int key,rad;
    struct BSTree *left, * right,*parent;
} BSTree;

void init(BSTree **tree)
{
    *tree=(BSTree *)malloc(sizeof(BSTree));
    (*tree)->key=0;
    (*tree)->rad=0;
    (*tree)->parent=NULL;
    (*tree)->left=NULL;
    (*tree)->right=NULL;
}

void free_tree(BSTree **tree)
{
    if((*tree)!=NULL)
    {
        free_tree(&((*tree)->left));
        free_tree(&((*tree)->right));
        free((*tree));
    }
}

int tsearch(BSTree *tree, int val)
{
    if(tree==NULL)
        return 0;
    if(tree->key==val)
        return 1;
    if(val<tree->key)
        return tsearch(tree->left,val);
    if(val>tree->key)
        return tsearch(tree->right,val);
}

int height(BSTree *tree)
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

void insert(BSTree *tree, int val)
{
    if(tree->parent==NULL&&tree->rad==0)
    {
        tree->key=val;
        tree->rad=1;
        return;
    }
    BSTree *node,*p;
    int ok=0;
    init(&node);
    node->key=val;
    if(tree->left==NULL&&val<tree->key)
    {
        tree->left=node;
        node->parent=tree;
        return;
    }
    if(tree->right==NULL&&val>tree->key)
    {
        tree->right=node;
        node->parent=tree;
        return;
    }
    if(val>tree->key)
    {
        free(node);
        insert(tree->right,val);
    }
    if(val<tree->key)
    {
        free(node);
        insert(tree->left,val);
    }
}

//by default succesorul numarului maxim este el insusi
BSTree* succesor(BSTree *tree)
{
    BSTree *node;
    if(tree==NULL)
        return NULL;
    if(tree->right==NULL)
        return tree;
    else
    {
        node=tree->right;
        while(node!=NULL&&node->left!=NULL)
            node=node->left;
        return node;
    }
}

BSTree* delete_node(BSTree *tree, int val)
{
    BSTree *save,*save2;
    if(tree==NULL)
        return NULL;
    if(val>tree->key)
        tree->right=delete_node(tree->right,val);
    else if(val<tree->key)
            tree->left=delete_node(tree->left,val);
    else
    {
        if(tree->left==NULL && tree->right==NULL)
        {
            if(tree->parent==NULL)
            {
                free(tree);
                return NULL;
            }
            else
            {
                if(tree->parent->key>tree->key)
                    tree->parent->left=NULL;
                if(tree->parent->key<tree->key)
                    tree->parent->right=NULL;
                free(tree);
                return NULL;
            }
        }
        else
        {
            if(tree->left==NULL)
            {
                save=tree->right;
                tree->right->parent=tree->parent;
                if(tree->parent!=NULL&&tree->parent->key>tree->key)
                    tree->parent->left=tree->right;
                if(tree->parent!=NULL&&tree->parent->key<tree->key)
                    tree->parent->right=tree->right;
                free(tree);
                return save;
            }
            else
            {
                if(tree->right==NULL)
                {
                    save=tree->left;
                    tree->left->parent=tree->parent;
                    if(tree->parent!=NULL&&tree->parent->key>tree->key)
                        tree->parent->left=tree->left;
                    if(tree->parent!=NULL&&tree->parent->key<tree->key)
                        tree->parent->right=tree->left;
                    free(tree);
                    return save;
                }
                else
                {
                    if(tree->left!=NULL&&tree->right!=NULL)
                    {
                        save=tree->left;
                        if(tree->parent==NULL)
                        {
                            save2=succesor(tree);
                            save2->left=save;
                            save->parent=save2;
                            tree->right->parent=tree->parent;
                            save=tree->right;
                            free(tree);
                            return save;
                        }
                        else
                        {
                            save2=succesor(tree);
                            save2->left=save;
                            save->parent=save2;
                            tree->right->parent=tree->parent;
                            if(tree->parent!=NULL&&tree->parent->key>tree->key)
                                tree->parent->left=tree->right;
                            if(tree->parent!=NULL&&tree->parent->key<tree->key)
                                tree->parent->right=tree->right;
                            save=tree->right;
                            free(tree);
                            return save;
                        }
                    }
                }
            }
        }
    }
    
    return tree;
    
}

void print_in_order(BSTree *tree)
{
    if(tree!=NULL)
    {
        print_in_order(tree->left);
        printf("%d ",tree->key);
        print_in_order(tree->right);
    }
}

void print_pre_order(BSTree *tree)
{
    if(tree!=NULL)
    {
        printf("%d ",tree->key);
        print_pre_order(tree->left);
        print_pre_order(tree->right);
    }
}

void print_post_order(BSTree *tree)
{
    if(tree!=NULL)
    {
        print_post_order(tree->left);
        print_post_order(tree->right);
        printf("%d ",tree->key);
    }
}

void file_print_in_order(BSTree *tree,FILE *f)
{
    if(tree!=NULL)
    {
        file_print_in_order(tree->left,f);
        fprintf(f,"%d ",tree->key);
        file_print_in_order(tree->right,f);
    }
}

//trebuie facut un if daca ramane arborele gol sa il reinitializam
int main()
{
    BSTree *tree;
    init(&tree);
    /*
    int i,n,j,val;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&val);
        insert(tree,val);
        //printf("%d\n",tsearch(tree,val));
        printf("%d\n",height(tree));
        print_pre_order(tree);
        printf("\n");
    }
    print_in_order(tree);
    printf("\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&val);
        tree=delete_node(tree,val);
        print_pre_order(tree);
        printf("\n");
    }
    */
    FILE *f1,*f2;
    f1=fopen("abc.in","r");
    f2=fopen("abc.out","w");
    char linie[10];
    int val;
    while(fgets(linie,10,f1)!=NULL)
    {
        switch (linie[0])
        {
            case '1':
            {
                val=atoi(linie+2);
                insert(tree,val);
                break;
            }
            case '2':
            {
                val=atoi(linie+2);
                tree=delete_node(tree,val);
                break;
            }
            case '3':
            {
                val=atoi(linie+2);
                fprintf(f2,"%d\n",tsearch(tree,val));
                break;
            }
            default:
                break;
        }
        file_print_in_order(tree,f2);
        fprintf(f2,"\n");

    }
    fclose(f1);
    fclose(f2);
    free_tree(&tree);
    return 0;
}