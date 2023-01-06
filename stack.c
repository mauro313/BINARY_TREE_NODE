#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// crea un stack
stack_t* stack_new(int maxsize){
  stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));
  if(new_stack == NULL){
    printf("memory cannot be reserved for a new stack pointer");
    exit(-1);  
  }
  new_stack->s = (t_elem_1*)malloc(maxsize*sizeof(t_elem_1));
  if(new_stack->s == NULL){
    printf("memory cannot be reserved for a t_elem pointer");
    free(new_stack);
    exit(-2);        
  }
  new_stack->top = 0;
  new_stack->maxsize = maxsize;
  return new_stack;    
}

// libera memoria de un stack
void stack_free(stack_t** s){
  if(s != NULL && *s != NULL){
    free((*s)->s);
    (*s)->s = NULL;
    free(*s);
    *s = NULL; 
  }
}

// retorna tamaño de un stack
int stack_getsize(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-3);    
  }
  return s->top;    
}

// retorna el tamaño maximo de un stack
int stack_getmaxsize(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-4);    
  }
  return s->maxsize;    
}

// retorna true si el stack esta vacio y false si no lo esta
bool stack_isempty(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-5);    
  }
  bool returned = false;
  if(s->top == 0){
    returned = true;    
  }
  return returned;
}

//retorna true si el stack esta lleno y false si no lo esta
bool stack_isfull(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-6);    
  }
  bool returned = false;
  if(s->top == s->maxsize){
    returned = true;    
  }
  return returned;
}

// agrega un elemento al stack.Retorna 1 si se agrego el valor y 0 en caso contrario(stack lleno).
int push(stack_t* s, t_elem_1 elem){
  if(s == NULL){
   printf("stack pointer is null");
   exit(-7);    
  }
  int returned = 0;
  if(!stack_isfull(s)){
    s->s[s->top] = elem;
    s->top++;
    returned = 1;    
  }
  return returned;     
}

// quita un elemento del stack
t_elem_1 pop(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-8);    
  }
  if(stack_isempty(s)){
    printf("stack is empty");
    exit(-9);  
  }
  t_elem_1 returned = s->s[s->top-1];
  s->top--;   
  return returned;
}

//visualiza el elemento tope del stack
t_elem_1 top(stack_t* s){
  if(s == NULL){
    printf("stack pointer is null");
    exit(-10);    
  }
  if(stack_isempty(s)){
    printf("stack is empty");
    exit(-11);  
  }
  return s->s[s->top];
}

// procedimiento para recorrer el stack usando una variable de contexto.
void stack_traverse(stack_t* stack,bool stack_do(t_elem_1,void*),void* context){
  if(stack == NULL){
    printf("stack pointer is NULL");
    exit(-12);  
  }  
  if(!stack_isempty(stack) && stack_do(top(stack),context)){
    t_elem_1 auxiliar = pop(stack);
    stack_traverse(stack,stack_do,context);
    push(stack,auxiliar);  
  }
}

