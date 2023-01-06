#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binary_tree_node.h"
#include "stack.h"

// creacion de un nuevo nodo 
btn_t* btn_new(t_elem value){
  btn_t* new_node = (btn_t*)malloc(sizeof(btn_t));
  if(new_node==NULL){
    printf("memory cannot be reserved for a btn new node");
    exit(-1); 
  }
  new_node->value=value;
  new_node->left=NULL;
  new_node->right=NULL;
  return new_node;
}

//Procedimiento para liberar la memoria deun nodo y sus hijos
void btn_free(btn_t** node){
  if(node!= NULL && *node!=NULL){
    btn_free(&(*node)->left);
    btn_free(&(*node)->right);
    free(*node);
    *node = NULL;
  }    
}

//Funcion que retorna el valor de un nodo
t_elem btn_get_value(btn_t* node){
  if(node == NULL){
    printf("btn node is NULL");
    exit(-2);  
  }
  return node->value;  
}

//Funcion que retorna el hijo izquierdo de un nodo
btn_t* btn_get_left_child(btn_t* node){
  if(node == NULL){
    printf("btn pointer is NULL");
    exit(-3);    
  }
  return node->left;
}

//Funcion que retorna el hijo derecho de un nodo
btn_t* btn_get_right_child(btn_t* node){
  if(node == NULL){
    printf("btn pointer is NULL");
    exit(-4);    
  }
  return node->right;    
}

//Funcion que retorna la referencia del hijo izquierdo de un nodo
btn_t** btn_get_left_child_reference(btn_t* node){
  if(node == NULL){
    printf("btn node pointer is NULL");
    exit(-5);  
  }
  return &node->left;  
}

//Funcion que retorna la referencia del hijo derecho de un nodo
btn_t** btn_get_right_child_reference(btn_t* node){
  if(node == NULL){
    printf("btn node pointer is NULL");
    exit(-6);
  }
  return &node->right;  
}

//retorna true si el nodo es hoja y false si no lo es
bool btn_isLeaf(btn_t* node){
  if(node == NULL){
    printf("btn pointer is null");
    exit(-7);    
  }  
  bool returned = false;
  if((node->left == NULL) && (node->right == NULL)){
    returned = true;
  }
  return returned;
}

// retorna la cantidad de nodos de un arbol binario
int btn_count(btn_t* node){
  int result = 0;
  if(node != NULL) {
    result = 1 + btn_count(node->left) + btn_count(node->right);
  }
  return result;
}

// retorna la referencia del nodo buscado si este se encuentra. Caso contrario retorna NULL.
btn_t** btn_find(btn_t** root, t_elem value, int (*compare)(t_elem, t_elem)){
  if(root == NULL){
    printf("btn double pointer is null");
    exit(-8);  
  }
  btn_t** returned = NULL;
  if(*root!=NULL && compare(btn_get_value(*root),value)!=0){
    returned = btn_find(&(*root)->left,value,compare);
    if(*root == NULL){
      returned = btn_find(&(*root)->right,value,compare);  
    }  
  }
  else{
    if(*root == NULL){
      returned = NULL;  
    }
    else{
      returned = root; 
    } 
  }
  return returned;
} 

// insercion de un nodo de forma balanceada    
void btn_insert(btn_t** root,btn_t* new_node){
  if(root == NULL){
    printf("btn double pointer is null");
    exit(-9);
  }
  if(*root == NULL){
    *root = new_node;  
  }
  else{
    if(btn_count((*root)->left)<=btn_count((*root)->right)){
      btn_insert(&(*root)->left,new_node);
    }
    else{
      btn_insert(&(*root)->right,new_node); 
    }
  }
}

//insercion de un valor
void btn_insert_value(btn_t** root,t_elem value){
  if(root == NULL){
    printf("btn double pointer is NULL");
    exit(-10);  
  }
  btn_t* new_node = btn_new(value);
  btn_insert(root,new_node);  
}

int _btn_level(btn_t* node, t_elem value, int level, int cmp(t_elem, t_elem)){
 int counter = 0;
 if(node == NULL){
   return -1;
 } 
 else{
   if(cmp(node->value,value)==0){
     return level;
   }
   else{
     counter = _btn_level(node->left,value,level+1,cmp);
     if(counter!=-1){
       return counter;
     }
     counter = _btn_level(node->right,value,level+1,cmp);
     if(counter!=-1){
       return counter;
     }
     return -1; 
   }
 }
}

//Funcion que retorna el nivel de un arbol
int btn_level(btn_t* root, t_elem value, int cmp(t_elem, t_elem)){
  int level = 0;
  if(root == NULL){
    return -1;
  }
  else{
    if(cmp(root->value,value)==0){
      return level;
    }
    else{
      int reference = _btn_level(root->left,value,level+1,cmp);
      if(reference==-1){
        reference = _btn_level(root->right,value,level+1,cmp);
      }
      return reference;
    }
  }
}

//recorrido inorden
void btn_inorder(btn_t* node,void btn_do(btn_t*, void*),void* ctx){
  if(node!=NULL){
    btn_inorder(node->left,btn_do,ctx);
    btn_do(node,ctx);
    btn_inorder(node->right,btn_do,ctx);
  }
}

//recorrido postorden 
void btn_postorder(btn_t* node, void btn_do(btn_t*, void*), void* ctx){
  if(node!=NULL){
    btn_postorder(node->left,btn_do,ctx);
    btn_postorder(node->right,btn_do,ctx);
    btn_do(node,ctx);
  }
}

//recorrido preorden
void btn_preorder(btn_t* node, void btn_do(btn_t*, void*), void* ctx){
  if(node!=NULL){
    btn_do(node,ctx);
    btn_preorder(node->left,btn_do,ctx);
    btn_preorder(node->right,btn_do,ctx);
  }
}

//recorrido inorder (uso de un stack como estructura auxiliar)
void btn_inorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack= stack_new(100);
    btn_t* auxiliar = root;
    while(auxiliar != NULL || !stack_isempty(stack)){
      while(auxiliar != NULL){
        push(stack,auxiliar);
        auxiliar = btn_get_left_child(auxiliar); 
      }
      auxiliar = pop(stack);
      btn_do(auxiliar,ctx);
      auxiliar = btn_get_right_child(auxiliar);       
    }
    stack_free(&stack);
  }
}

//recorrido postorder
void btn_postorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack_in = stack_new(100);
    stack_t* stack_out = stack_new(100);
    btn_t* auxiliar = root;
    push(stack_in,auxiliar);
    while(!stack_isempty(stack_in)){
      auxiliar = pop(stack_in);
      push(stack_out,auxiliar);
      if(btn_get_left_child(auxiliar)!=NULL){
        push(stack_in,auxiliar);  
      }
      if(btn_get_right_child(auxiliar)!=NULL){
        push(stack_in,auxiliar);  
      }  
    }
    while(!stack_isempty(stack_out)){
      auxiliar = pop(stack_out);
      btn_do(auxiliar,ctx);   
    }
    stack_free(&stack_in);
    stack_free(&stack_out);  
  }
}

//recorrido preorder
void btn_preorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx){
  if(root != NULL){
    stack_t* stack= stack_new(100);
    btn_t* auxiliar = root;
    while(auxiliar != NULL || !stack_isempty(stack)){
      while(auxiliar != NULL){
        push(stack,auxiliar);
        btn_do(auxiliar,ctx);
        auxiliar = btn_get_left_child(auxiliar); 
      }
      auxiliar = pop(stack);
      auxiliar = btn_get_right_child(auxiliar);       
    }
    stack_free(&stack);
  }
}

int _max(int a, int b) { return (a > b) ? a : b; }

// funcion que retona la altura de un nodo
int btn_height(btn_t* node) {
  if(node == NULL){
    return -1;
  }
  else{
    return 1+_max(btn_height(node->left),btn_height(node->right)); 
  }
}


int _btn_print(btn_t* tree, int is_left, int offset, int depth, char s[20][255], void toStr (btn_t*, char*)) {
    char b[200];
    int width = 5;

    if (!tree) return 0;
    toStr(tree, b);
    //sprintf(b, "%s", str);
    

    int left = _btn_print(tree->left, 1, offset, depth + 1, s, toStr);
    int right = _btn_print(tree->right, 0, offset + left + width, depth + 1, s, toStr);

    // for (int i = 0; i < width; i++) s[2 * depth][offset + left + i] = b[i];
    for (int i = 0; i < strlen(b); i++) s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }
    
    return left + width + right;
}

/**
 * Dibuja un árbol binario con caracteres
 * (Los valores de los nodos deben estar entre 0 y 999).
 */
void btn_print(btn_t* tree, void toStr (btn_t*, char*)) {
    char s[20][255];
    for (int i = 0; i < 20; i++) sprintf(s[i], "%80s", " ");

    _btn_print(tree, 0, 0, 0, s, toStr);

    for (int i = 0; i < 20; i++) {
        int j = 0;
        while (s[i][j] != '\0' && s[i][j] == ' ') {
            j++;
        }
        if (s[i][j] != '\0') {
            printf("%s\n", s[i]);
        }
    }
}

//Procedimiento para asignar un hijo izquierdo a un nodo
int btn_left_child_assign(btn_t** root,btn_t* left_child){
  if(root == NULL){
    printf("btn double pointer is NULL");
    exit(-11);  
  }
  int returned = 0;
  if(*root != NULL){
    (*root)->left = left_child;
    returned = 1;  
  }
  return returned;  
}

//Procedimiento para asignar un hijo derecho a un nodo
int btn_right_child_assign(btn_t** root,btn_t* right_child){
  if(root == NULL){
    printf("btn double pointer is NULL");
    exit(-12);  
  }
  int returned = 0;
  if(*root != NULL){
    (*root)->right = right_child;
    returned = 1;  
  } 
  return returned;
}



