#ifndef BINARY_TREE_NODE_H_INCLUDED
#define BINARY_TREE_NODE_H_INCLUDED
#include "stdbool.h"
#define t_elem int

typedef struct _btn {
  t_elem value;
  struct _btn *left;
  struct _btn *right;
}btn_t;

btn_t* btn_new(t_elem value);

void btn_free(btn_t** node);

t_elem btn_get_value(btn_t* node);

btn_t* btn_get_left_child(btn_t* node);

btn_t* btn_get_right_child(btn_t* node);

btn_t** btn_get_left_child_reference(btn_t* node);

btn_t** btn_get_right_child_reference(btn_t* node);

bool btn_isLeaf(btn_t* node); 

int btn_count(btn_t* node); 

btn_t** btn_find(btn_t** root, t_elem value, int cmp(t_elem, t_elem)); 

void btn_insert(btn_t** root, btn_t* new_node); 

void btn_insert_value(btn_t** root, t_elem value);  

int _btn_level(btn_t* node, t_elem value, int level, int cmp(t_elem, t_elem));

int btn_level(btn_t* root, t_elem value, int cmp(t_elem, t_elem));

void btn_inorder(btn_t* root, void btn_do(btn_t*, void*), void* ctx);

void btn_postorder(btn_t* root, void btn_do(btn_t*, void*), void* ctx);

void btn_preorder(btn_t* root, void btn_do(btn_t*, void*), void* ctx);

void btn_inorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx);

void btn_postorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx);

void btn_preorder_iterativeStack(btn_t* root, void btn_do(btn_t*,void*),void* ctx);

int _max(int a, int b);

int btn_height(btn_t* node);

int _btn_print(btn_t* tree, int is_left, int offset, int depth, char s[20][255], void toStr (btn_t*, char*));

void btn_print(btn_t* tree, void toStr (btn_t*, char*));

int btn_left_child_assign(btn_t** root,btn_t* left_child);

int btn_right_child_assign(btn_t** root,btn_t* right_child);

#include "binary_tree_node.c"

#endif //BINARY_TREE_NODE_H_INCLUDED

