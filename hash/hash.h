#include <stdlib.h>

typedef struct block {
  void * entry;

  // do the linked list implementation
  struct block * next;
} block;

typedef struct hash{
  struct block *buckets;
} hash;


hash * hash_init(unsigned int size);
