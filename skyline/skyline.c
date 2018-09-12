#include "skyline.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
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

void city_print(city * c){
  for(building *  head = c->head;
      head!=NULL; head=head->next)
    printf("{%d,%u,%d} ", head->left, head->ht, head->right);
  printf("\n");
}

building * building_create(int data[3]){
  building * b = (building *) malloc(sizeof(building));
  b->left=data[0];
  b->ht=data[1];
  b->right=data[2];
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
  int min_left = head->left;
  building * min_b = head;
  while(head!=NULL){
    if (min_left > head->left){
      min_left = head->left;
      min_b = head;
    }
    head=head->next;
  }
  return min_b;
}
building * most_right(city * c){
  building * head = c->head;
  int min_left = head->left;
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
skyline *  skyline_merge(skyline * s1, skyline * s2){
  // merge skyline s2 into s1
  
  unsigned int len1 = s1->length;
  unsigned int len2 = s2->length;
  int temp[2] = {0}; // a placeholder for a skyline point.
  // add the extending data points from s2 to s1
  s1->data = (int (*)[2]) realloc(s1->data, (len1+len2)*sizeof(int[2]));
  // fix overlaping skylines.
  if (s1->data[len1-1][0] > s2->data[0][0] &&
      s1->data[len1-1][1] > s2->data[0][1]){
#ifdef DEBUG
    printf("First case\n");
    skyline_print(s1);
    skyline_print(s2);
#endif
    temp[0] = s1->data[len1-1][0];
    temp[1] = s1->data[len1-1][1];
    s1->data[len1-1][0] = s2->data[0][0];
    s1->data[len1-1][1] = s2->data[0][1];
    s1->data[len1][0] = temp[0];
    s1->data[len1][1] = temp[1];
    for (int i = len1+1; i<len1+len2; i++){
      s1->data[i][0] = s2->data[i-len1][0];
      s1->data[i][1] = s2->data[i-len1][1];
    }
  }
  else if(s1->data[len1-1][0] > s2->data[0][0] &&
	  s1->data[len1-1][1] < s2->data[0][1]){
#ifdef DEBUG
    printf("Second case\n");
    skyline_print(s1);
    skyline_print(s2);
#endif
    s1->data[len1-1][0] = s2->data[0][0];
    s1->data[len1-1][1] = s2->data[0][1];
    for (int i = len1; i<len1+len2-1; i++){
      s1->data[i][0] = s2->data[i-len1+1][0];
      s1->data[i][1] = s2->data[i-len1+1][1];
    }
  }
    else
#ifdef DEBUG
    printf("else case\n");
    skyline_print(s1);
    skyline_print(s2);
#endif      
    for (int i = len1; i<len1+len2; i++){
      s1->data[i][0] = s2->data[i-len1][0];
      s1->data[i][1] = s2->data[i-len1][1];
    }

  s1->length += len2;
  // free memory of s2
  skyline_free(s2);
  s2=NULL;

  return s1;
}

skyline * skyline_init(int (* data)[2], unsigned int length){
  unsigned int len_data = sizeof(data)/sizeof(data[0]);
  skyline * s;
  s = (skyline *) malloc(sizeof(data)+sizeof(s->length));
  
  s->data = data;
  s->length = length;
  
  return s;
}

void skyline_print(skyline * s){
  for (int i = 0; i<s->length; i++)
    printf("(%d %d) ", s->data[i][0], s->data[i][1]);
  printf("\n");
}

void skyline_free(skyline * s){
  free(s->data);
  
  free(s);
}

skyline * find_skyline(city * c){
  int (* new_skyline)[2];
  building * bl;
  building * br;
  skyline * s;
  city c2[1];
    
  switch (c->length){
  case 2:
    // get the building most to the left
#ifdef DEBUG
    printf("Hello in case 2\n");
#endif
    // assume correct order.
    bl = c->head;
    br = bl->next;

    if (bl->right > br->right &&
	bl->ht >= br->ht){
      new_skyline = (int (*)[2] ) malloc(2*sizeof(skyline));
      new_skyline[0][0] = bl->left;
      new_skyline[0][1] = bl->ht;
      new_skyline[1][0] = bl->right;
      new_skyline[1][1] = 0;
      
      s = skyline_init(new_skyline, 2);
    }
    else if (bl->left < br->left &&
	bl->ht <= br->ht){
      new_skyline = (int (*)[2] ) malloc(2*sizeof(skyline));
      new_skyline[0][0] = br->left;
      new_skyline[0][1] = br->ht;
      new_skyline[1][0] = br->right;
      new_skyline[1][1] = 0;
      
      s = skyline_init(new_skyline, 2);
    }
    else if (bl->right > br->left &&
	     bl->ht >= br->ht){
      new_skyline = (int (*)[2] ) malloc(4*sizeof(skyline));
      new_skyline[0][0] = bl->left;
      new_skyline[0][1] = bl->ht;
      new_skyline[1][0] = bl->right;
      new_skyline[1][1] = bl->ht;
      new_skyline[2][0] = br->left;
      new_skyline[2][1] = br->ht;
      new_skyline[3][0] = br->right;
      new_skyline[3][1] = 0;
      
      s = skyline_init(new_skyline, 4);
    }
    else if (bl->right > br->right &&
	bl->ht < br->ht){
      new_skyline = (int (*)[2] ) malloc(3*sizeof(skyline));
      new_skyline[0][0] = bl->left;
      new_skyline[0][1] = bl->ht;
      new_skyline[1][0] = br->left;
      new_skyline[1][1] = br->ht;
      new_skyline[2][0] = br->right;
      new_skyline[2][1] = 0;
      
      s = skyline_init(new_skyline, 3);
    }
    else{
      new_skyline = (int (*)[2] ) malloc(4*sizeof(skyline));
      new_skyline[0][0] = bl->left;
      new_skyline[0][1] = bl->ht;
      new_skyline[1][0] = bl->right;
      new_skyline[1][1] = 0;
      new_skyline[2][0] = br->left;
      new_skyline[2][1] = br->ht;
      new_skyline[3][0] = br->right;
      new_skyline[3][1] = 0;
      s = skyline_init(new_skyline, 4);
    }

    city_free(c);
    return s;
    
  
  default:
    // divide!
#ifdef DEBUG
    city_print(c);
    printf("city length = %u\n", c->length);
#endif
    city_init(c2);
    if(city_split(c, c2) == NULL)
      exit(1);
#ifdef DEBUG
    if(c2->head == NULL){
      city_print(c);
      city_print(c2);
      perror("The new city did not get any buildings\n");
    }
#endif

    s = skyline_merge(find_skyline(c), find_skyline(c2));
    


    return s; // if this is reached something bad happend.
  }
}

city * city_split(city * c, city * c2){
  // function that takes the first half of the city and and store it x separate city pointer struct
  unsigned int len = c->length;
  building * head = c->head;
  unsigned int i = 0;
  while(head != NULL && i<len/2-1){
    head = head->next;
    i++;
  }
  c2->head = head->next;
  c2->length=len/2;
  c->length-=len/2;
  // dereference pointer
  head->next = NULL;
  return c2;
}
