#include "hash.h"

block * buckets_init(unsigned int size){
  block * buckets = (block *) malloc(sizeof(block)*size);
  return buckets;
}

hash * hash_init(unsigned int size){
  hash * h;
  h = (hash *) malloc(sizeof(hash));
  h->buckets = buckets_init(size);
  return h;
}

void insert(hash * h, void * entry_data, void * entry){
  // get hash value
  unsigned int hash;
  hash = hash_function(entry, entry_data);

  //insert into hash table
  block * b = h->(blocks+hash);
  void * b_entries = b->entry;
  if (b_entries == NULL){
    // insert the first element in the block
    b_entries 
  }
  
}
