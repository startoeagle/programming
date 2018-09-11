typedef struct node_t{
  struct node_t * next;
  int data;
}node;

typedef struct list_t{
  struct node_t * head;
  unsigned int length;
} list;


void init_list(list *l);
void list_push(list * l, int data);
void list_append(list * l, int data);
void list_pop(list * l);
void list_print(list * l);
void list_free(list * l);
void node_destroy(list * l, unsigned int pos);
