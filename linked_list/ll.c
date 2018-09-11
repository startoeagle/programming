// linked list functions and stuff
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>


void init_list(list *l){
  l->head = NULL;
  l->length = 0;
}

void list_push(list * l, int data){
  // create a node
  node * n = (node *) malloc(sizeof(node));
  n->next = l->head;
  n->data = data;
  l->head = n;
  l->length++;
}

void list_append(list * l, int data){
  node * n = (node *) malloc(sizeof(node));
  n->data = data;
  n->next = NULL;
  node * h = l->head;
  while(h->next != NULL)
    h=h->next;
  h->next = n;
  
}

void list_pop(list * l){
  node * h = l -> head;
  l->head = l->head->next;
  free(h);
  h = NULL;
}

void list_print(list * l){
  node * n = l->head;
  while(n != NULL){
    printf("%d ", n->data);
    n=n->next;
  }
  printf("\n");
}

void list_free(list * l){
  node * h = l->head;
  while(h != NULL){
    l->head = l->head->next;
    free(h);
    h = l->head;
  }
  
}


void node_destroy(list * l, unsigned int pos){
  node * h = l->head;
  while(pos>1 && h!=NULL){
    h = h->next;
    pos--;
  }
  node * n = h->next;
  h->next = h->next->next;
  free(n);
  n = NULL;
}
