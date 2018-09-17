#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
  unsigned int size;
  struct node_t * next;
} node;
typedef struct list_t{
  struct node_t * head;
} list;

void pole_init(list * l){
  l->head = NULL;
}

node * node_init(unsigned int size){
  node * n = (node *) malloc(sizeof(node));
  n->size = size;
  n->next = NULL;
  return n;
}

void list_free(list * l){
  node * tmp;
  node * current = l->head;

  while(current){
    tmp = current->next;
    free(current);
    current = tmp;
  }
}

void push(list * l, unsigned int size){

  node * tmp = l->head;
  l->head = node_init(size);
  l->head->next = tmp;
}

void move_from_to(list * src, list * dst){
  // move the top from src to dst
  node * n = src->head;
  src->head = src->head->next;
  node * tmp = dst->head;
  n->next = tmp;
  dst->head = n;
}

void print(list *  l){
  if(l->head == NULL)
    return;
  node * n = l->head;
  while(n != NULL){
    printf("%u ", n->size);
    n = n->next;
  }
  printf("\n");
}


  
void hanoi(list * start, list * work, list * final, unsigned int n);
int main(const int argc, char  * argv[]){
  // get number of disks
  if (argc != 2){
    printf("Enter an integer as an argument\n");
    return 0;
  }
    
  const int n = atoi(argv[1]);

  list poles[3];
  int i;
  for(i = 0; i<3; i++){
    pole_init(&poles[i]);
  }

  // fill the first pole.
  for(i=n; i>0; i--){
    push(&poles[0], (unsigned int) i);
  }

#ifdef TEST
  printf("printing poles\n");
  for (i = 0; i<3; i++){
    printf("i = %d\n", i);
    print(&poles[i]);
  }


  move_from_to(&poles[0], &poles[1]);

  
  for (i = 0; i<3; i++)
    print(&poles[i]);
#endif
  for (i = 0; i<3; i++){
    printf("pole %d \n", i+1);
    print(&poles[i]);
  }
  hanoi(poles, poles+1, poles+2, n);

  for (i = 0; i<3; i++){
    printf("pole %d \n", i+1);
    print(&poles[i]);
  }

  
  for (i = 0; i<3; i++)
    list_free(&poles[i]);

  
  return 0;
}


void hanoi(list * start, list * work, list * final, unsigned int n){
  // move the largest disk to the right

  if (n == 1)
    move_from_to(start, final);
  else{
    hanoi(start, final, work,  n-1);
    move_from_to(start, final);
    hanoi(work, start, final, n-1);
  }
}
