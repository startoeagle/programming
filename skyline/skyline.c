#include "skyline.h"
#include <stdlib.h>
void city_init(city * c){
  c -> head = NULL;
  c->length=0;
}

void city_push(city * c, building * b){
  b->next = c->head;
  c->head = b;
  c->length++;
}

void city_merge(city * c, city * c2){
  // merge c2 into c1;
  building * head = c->head;
  while(head!=NULL)
    head = head->next;
  head = c2->head;
  c2->head = NULL;
}

building * building_create(int data[3]){
  building * b = (building *) malloc(sizeof(building));
  b->left=data[0];
  b->ht=data[1];
  b->right=data[3];
  return b;
}

void city_free(city * c){
  building * head = c->head;
  building * temp;
  while(head!=NULL){
    temp = head;
    head=head->next;
    free(temp);
  }
}

building * most_left(city * c){
  building * head = c->head;
  int min_left = h->left;
  building * min_b = head;
  while(head!=NULL){
    if (min_left < head->left){
      min_left = head->left;
      min_b = head;
    }
    head=head->next;
  }
  return min_b;
}


skyline * find_skyline(city * c){
  if (c->length == 2){
    // get the building most to the left
    building * b = most_left(c);
    skyline * s = skyline_append(b->left, b->right);
    return s;
  }
  else{
    // divide!
    city * c2 = city_split(c);
    skyline_merge(find_skyline(c), find_skyline(c2));
  }
    
}
