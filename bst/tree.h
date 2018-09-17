#include <stdlib.h>
#include <stdio.h>

typedef struct node_t{
  int val; // store what is needed to be stored here
  struct node_t * left;
  struct node_t * right;
} node;

typedef struct tree_t{
  struct node_t * head;
} tree;



tree * tree_init();
node * node_init();
void insert(tree * t, int val);
void tree_free(tree * t);
void tree_print(tree * t);
