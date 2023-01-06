#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>
#define t_elem_1 void*

typedef struct{
  t_elem_1* s;
  int top;
  int maxsize;
}stack_t;

stack_t* stack_new(int maxsize);

void stack_free(stack_t** s);

int stack_getsize(stack_t* s);

int stack_getmaxsize(stack_t* s);

bool stack_isempty(stack_t* s);

bool stack_isfull(stack_t* s);

int push(stack_t* s, t_elem_1 elem);

t_elem_1 pop(stack_t* s);

t_elem_1 top(stack_t* s);

void stack_traverse(stack_t* stack,bool stack_do(t_elem_1,void*),void* context);

#include "stack.c"
#endif // STACK_H_INCLUDED