#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree_node.h"
#include "stack.h"

btn_t* btn_int(int amount_of_nodes);
void btn_intTostring(btn_t* node, char* string);
void btn_do_addition(btn_t* node,void* context);
bool even_node_check(btn_t* node);
bool tree_of_even(btn_t* root);
void mirror_tree(btn_t** root);
void btn_doPrintfElem(btn_t* node,void* ctx);
void btn_doAddToStack(btn_t* node, void* context);
void stack_printf(stack_t* stck, void (*print_elem)(t_elem));
void print_telem(t_elem value);
btn_t* mirror_tree_creation(btn_t* root);


int main(void){
  btn_t* root = btn_int(15);
  btn_t* root_mirror = NULL;
  stack_t* stack_in = stack_new(15);
  stack_t* stack_pre = stack_new(15);
  stack_t* stack_post = stack_new(15);
  int addition = 0;
  
  //impresion del arbol
  btn_print(root,btn_intTostring);
  
  //arbol en espejo
  mirror_tree(&root);
  
  //impresion del arbol 
  printf("\n\n");
  btn_print(root,btn_intTostring);

  //creacion de un arbol en espejo
  root_mirror = mirror_tree_creation(root);
  
  //impresion del arbol en espejo
  printf("\n\n");
  btn_print(root_mirror,btn_intTostring);

  //suma de los elementos
  printf("\n\n");
  btn_inorder(root,btn_do_addition,&addition);
  printf("the addition of all elements : %i",addition);
  
  //impresion inorder postorder preorder
  
  printf("\nelements inorder:\n");
  btn_inorder(root,btn_doAddToStack,stack_in);
  stack_printf(stack_in,print_telem);
  
  printf("\nelements preorder:\n");
  btn_preorder(root,btn_doAddToStack,stack_pre);
  stack_printf(stack_pre,print_telem);
  
  printf("\nelements postorder:\n");
  btn_postorder(root,btn_doAddToStack,stack_post);
  stack_printf(stack_post,print_telem);
  
  //liberacion de toda la memoria usada
  btn_free(&root);
  stack_free(&stack_in);
  stack_free(&stack_pre);
  stack_free(&stack_post);
  return 0;    
}
//**************** Ejemplos de aplicacion************************//

//crea un arbol de enteros
btn_t* btn_int(int amount_of_nodes){
  btn_t* root = NULL;
  srand(time(NULL));
  for(int i=0;i<amount_of_nodes;i++){
    btn_insert_value(&root,rand()%100);          
  }
  return root;
}

//procedimiento auxiliar para los recorridos
void btn_doPrintfElem(btn_t* node,void* ctx){
  printf("%i ",btn_get_value(node));  
}

//procedimiento auxiliar
void print_telem(t_elem value){
  printf("%i ",value);  
}

//procedimiento auxiliar para los recorridos
void btn_intTostring(btn_t* node, char* string){
  if(node==NULL){
    printf("btn node is NULL");
    return;  
  }
  sprintf(string,"(%03d)",btn_get_value(node));  
} 

//suma elementos de los nodos de un arbol
void btn_do_addition(btn_t* node,void* context){
  if(node!=NULL){
    *(int*)context += btn_get_value(node);  
  }  
}

// funcion que retora true si el contenido de un nodo no es par y false si lo es 
bool even_node_check(btn_t* node){
  bool returned = true;
  if(btn_get_value(node)%2!=0){
    returned = false;  
  }
  return returned; 
}

// funcion que retorna true si todos los elementos son pares y false en caso contrario
bool tree_of_even(btn_t* root){
  return (root == NULL)||((even_node_check(root))&&(tree_of_even(btn_get_left_child(root)))&&(tree_of_even(btn_get_right_child(root))));  
}


//procedimiento para obtener el arbol en espejo.
void mirror_tree(btn_t** root){
  if(*root != NULL){
    mirror_tree(btn_get_left_child_reference(*root));
    mirror_tree(btn_get_right_child_reference(*root));
    btn_t* auxiliar = btn_get_left_child(*root);
    btn_left_child_assign(root,btn_get_right_child(*root));
    btn_right_child_assign(root,auxiliar);
  }    
}

//funcion para crear un arbol en espejo
btn_t* mirror_tree_creation(btn_t* root){
  btn_t* new_node = NULL;
  if(root!=NULL){
    new_node = btn_new(btn_get_value(root));
    btn_right_child_assign(&new_node,mirror_tree_creation(btn_get_left_child(root)));
    btn_left_child_assign(&new_node,mirror_tree_creation(btn_get_right_child(root)));  
  }
  return new_node;    
}

//**********Procedimiento para obtener los nodos en una estructura dinámica (stack)
//********** en los tres recorridos(inorder, postorder, preorder)

void btn_doAddToStack(btn_t* node, void* context){
  if(context != NULL){
    context = (stack_t*)context;
    push(context,node);  
  }  
}

void stack_printf(stack_t* stck, void (*print_elem)(t_elem)){
  if(!stack_isempty(stck)){
    btn_t* auxiliar = pop(stck);
    print_elem(btn_get_value(auxiliar));
    stack_printf(stck,print_elem);
    push(stck,auxiliar); 
  }    
}
