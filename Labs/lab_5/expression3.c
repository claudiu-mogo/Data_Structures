#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    int data;
    char exp;
    struct node* next;
} node;

typedef struct Stack {
    node *top;
    int len;
} Stack;

void init_Stack(Stack** s)
{
    *s=(Stack*)malloc(sizeof(Stack));
    (*s)->top=NULL;
    (*s)->len=0;
}

void free_Stack(Stack** s)
{
    node *p;
    while((*s)->top!=NULL)
    {
        p=(*s)->top;
        (*s)->top=(*s)->top->next;
        free(p);
    }
    free(*s);
}

int add_int_stack (Stack *s, int val)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->data=val;
    new_node->next=NULL;
    new_node->next=s->top;
    s->top=new_node;
    s->len++;
    return 1;
}

char add_char_stack (Stack *s, char c)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node==NULL)
        return 0;
    new_node->exp=c;
    new_node->next=NULL;
    new_node->next=s->top;
    s->top=new_node;
    s->len++;
    return 1;
}

int pop_int_stack(Stack *s)
{
    if(s->len>0)
    {
        node *p=s->top;
        s->top=s->top->next;
        int v=p->data;
        free(p);
        s->len--;
        return v;
    }
    exit(1);
}

char pop_char_stack(Stack *s)
{
    if(s->len>0)
    {
        node *p=s->top;
        s->top=s->top->next;
        char v=p->exp;
        free(p);
        s->len--;
        return v;
    }
    exit(1);
}

void print_int_Stack(Stack *s)
{
    node *p=s->top;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

void print_char_Stack(Stack *s)
{
    node *p=s->top;
    while(p!=NULL)
    {
        printf("%c ",p->exp);
        p=p->next;
    }
    printf("\n");
}

int is_empty_Stack(Stack *s)
{
    if(s->len==0)
        return 1;
    return 0;
}

////////////////////////////

int precedence(char op)
{
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}

int applyOp(int a, int b, char op)
{
    switch(op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}

int evaluate(char* tokens)
{
    int i,rubbish;
    Stack *values, *ops;
    init_Stack(&values);
    init_Stack(&ops);
    char garbage;
    for(i=0;i<strlen(tokens);i++)
    {
        if(tokens[i] == ' ')
            continue;
        else if(tokens[i] == '(')
        {
            garbage=add_char_stack(ops,tokens[i]);
        }
        else if(isdigit(tokens[i]))
        {
            int val=0;
            while(i < strlen(tokens) && isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
            rubbish=add_int_stack(values,val);
            i--;
        }
        else if(tokens[i] == ')')
        {
            while(!is_empty_Stack(ops)&&ops->top->exp!='(')
            {
                int val2=values->top->data;
                rubbish=pop_int_stack(values);
                int val1=values->top->data;
                rubbish=pop_int_stack(values);
                char op=ops->top->exp;
                garbage=pop_char_stack(ops);
                rubbish=add_int_stack(values,applyOp(val1,val2,op));
            }
            if(!is_empty_Stack(ops))
                garbage=pop_char_stack(ops);
        }
        else
        {
            while(!is_empty_Stack(ops)&&precedence(ops->top->exp)>=precedence(tokens[i]))
            {
                int val2=values->top->data;
                rubbish=pop_int_stack(values);
                int val1=values->top->data;
                rubbish=pop_int_stack(values);
                char op=ops->top->exp;
                garbage=pop_char_stack(ops);
                rubbish=add_int_stack(values,applyOp(val1,val2,op));
            }
            garbage=add_char_stack(ops,tokens[i]);
        }
    }
    while(!is_empty_Stack(ops))
    {
        int val2=values->top->data;
        rubbish=pop_int_stack(values);
        int val1=values->top->data;
        rubbish=pop_int_stack(values);
        char op=ops->top->exp;
        garbage=pop_char_stack(ops);
        rubbish=add_int_stack(values,applyOp(val1,val2,op));
    }
    int rez=values->top->data;
    free_Stack(&values);
    free_Stack(&ops);
    return rez;
}

int main()
{
    printf("%d\n",evaluate("(10 + 2)/ 6"));
    return 0;
}