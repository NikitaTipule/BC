#include<stdio.h>
#include<stdlib.h>
#include "bc.h"


//operations on oparator stack
void init_os(ostack *s, int len){
    s->a = (char*)malloc(sizeof(char)*len);
    s->size = len;
    s->top = -1;
}

int isFull_os(ostack s) {
    if(s.top == s.size-1)
        return 1;
    else
        return 0;
}
 
int isEmpty_os(ostack s) {
    if(s.top == -1)
        return 1;
    else
        return 0;
}


//push an operator into the operator stack
void push_os(ostack *s, char d){
    if(isFull_os(*s))
        return;
    else {
        s->top++;
        s->a[s->top] = d;
        return;
    }
}

//pop an operator from the operator stack
char pop_os(ostack *s){ 
    char e = '#';
    if(!isEmpty_os(*s)){
        e = s->a[s->top];
        s->top--;
    }
    return e;

}

char peek(ostack s){
        return s.a[s.top];
}


//operations on the operand stack


void init_ps(pstack *s, int len){
    s -> size = len;
    s -> top = -1;
    s -> arr = (node**)malloc(sizeof(node *) * len);
    return;
}


int isEmpty_op(pstack ps) {
    if(ps.top == -1) 
        return 1;
    else return 0;
}

int isFull_op(pstack ps) {
    if(ps.top == (ps.size - 1)) {
        return 1;
    }
    else return 0;
}

void init_num(pstack *ps) {
    ps -> top++;
    ps -> arr[ps->top] = NULL;
}
void init(node **l) {
    *l = NULL;
    return;
}

void push_op(pstack *s, node *p) {
//    init_num(s);
    s -> top++;
    s -> arr[s -> top] = NULL;
    s -> arr[s -> top] = p;
    return;
}

node* pop_op(pstack *s) {
    node *e = NULL;
    if(!isEmpty_op(*s)) {
        e = s->arr[s->top];
        s -> arr[s-> top] = NULL;
        s->top--;
    }
    else {
        printf("Stack is empty");
    }
    return e;
}

node* peek_op(pstack s) {
    node *t = NULL;
    if(!isEmpty_op(s)) {
        return s.arr[s.top];
    }
    else {
        printf("Stack is empty\n");
        return NULL;
    }
}

//insert a digit into a number
void insert_dig(list *n, int d) {
    node *new = NULL, *p = (*n);
    new = (node*)malloc(sizeof(node));
    if(new) {
        new -> dig = d;
        new -> next = NULL; 
        new -> prev = NULL;
    }
    else return;
    
    //chacking wheather the it is a first digit or not
    if((*n) == NULL) {
        (*n) = new;
        return;
    }
    else {
        while(p -> next != NULL) {
            p = p -> next;
        }
        p -> next = new;
        new -> prev = p;
        new -> next = NULL;
        return;
    }
}