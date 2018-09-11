#include <stdio.h>
#include "ll.h"

#include <stdlib.h>
int main(){

  // create a list
  list *l = (list*) malloc(sizeof(list));
  init_list(l);
  list_push(l, 123);
  list_push(l, 1);
  list_push(l, 2);

  list_print(l);

  list_pop(l);
  list_print(l);

  list_append(l, 500);
  list_print(l);

  node_destroy(l,1);
  list_print(l);

  list_push(l, 12332);
  list_print(l);
  list_free(l);
  free(l);
  return 0;
}
