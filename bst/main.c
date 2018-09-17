#include<stdio.h>
#include "tree.h"
int main(){

  tree * t = tree_init();

  insert(t, 2);
  tree_print(t);
  insert(t, 6);
  tree_print(t);
  insert(t, 7);
  tree_print(t);
  insert(t, 4);
  insert(t, 1);
  insert(t, 9);
  insert(t, 3);

  tree_print(t);

  tree_free(t);
  
  return 0;
}
