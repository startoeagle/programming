#include "trie.h"
node * node_init(){
  node * n = (node *) malloc(sizeof(node));
  n->end_key = false;
  for (unsigned int i = 0; i<ALPHABET_SIZE; i++){
    n->children[i] = NULL;
  }
  return n;
}
void trie_init(trie * t){
  t->head = node_init();
  t->nr_words=0;
}

int get_index(char c){
  // get the index of each char
  return c - 'a';
}
char get_char(int index){
  return (char) (index + ((int) 'a'));
}

void insert(trie * t, char key[]){
  t->nr_words += 1;
  int  index;
  int len = strlen(key);
  node * head = t->head;
  // head = node_init();
  for(int i = 0; i<len; i++){
     // check if the child node has been created
    index = get_index(key[i]);
    if(head->children[index] == NULL)
      head->children[index] = node_init();
    
    // move head
    head = head->children[index];
  }

  // the last char is also end of word
  head->end_key = true;

 }

bool search(trie * t, char key[]){
  node * head = t->head;
  int index;
  for (int i = 0; i<strlen(key); i++){
    index = get_index(key[i]);
    if((head->children[index] == NULL) && !head->end_key){
      printf("%s does not match any key\n", key);
      return false;
    }
    else if(head->children[index]!= NULL && !head->end_key){
      head = head->children[index];
    }
    else{
      exit(1);
    }
  }

  
  if ((head->children[index] == NULL) && head->end_key){
    printf("%s is a complete key in this tier!\n", key);
    return true;
  }
  else{
    // when this code is reached, display the keys that fit the input key
  
    printf("%s matches a term\n", key);
    return true;
  }
}

bool match(trie * t, char key[]){
  node * head = t->head;
  int index;
  for (int i = 0; i < strlen(key); i++){
    index = get_index(key[i]);
    if (head->children[index]!=NULL){
      head = head->children[index];
    }
    else
      return false;
  }
  if (head->end_key)
    return true;
  else
    return false;
}

bool is_prefix(trie * t, char key[]){
  // returns true if the key key[] is a prefix to another key
  // goto en d key
  node * head = t->head;
  int index;
  for (int i = 0; i<strlen(key); i++){
    index = get_index(key[i]);
    head = head->children[index];
  }
  for (int j = 0; j<strlen(key); j++){
    if (head->children[j] != NULL)
      return true;
  }

  // when this code is reached no key countinen after argument key
  return false;
}

bool contains_prefix(trie * t, char key[]){
  // Check if the argument char * contains any end_key=true
  node * head = t->head;
  int index;
  for(int i = 0; i<strlen(key)-1; i++){
    index = get_index(key[i]);
    if(head->children[index]->end_key == true)
      return true;
    head = head->children[index];
  }
  return false;
}

void node_remove(trie * t, char key[]){
  // check if key exist in directory
  node * current  = t->head;
  t->nr_words--;
  int i, index;
  int len = strlen(key);
  if(match(t, key) && !is_prefix(t, key) && !contains_prefix(t, key)){
    // delete all nodes in key if there are no prefixes the key is a
    // part of, or there are no prefixes of the key that also is a
    // key.
    index = get_index(key[0]);
    node_free(current->children[index]);
    free(current->children[index]);
    current->children[index] = NULL;
  
  }
  else if (match(t, key) && is_prefix(t, key)){
    // the argument key is a prefix of another key, then unmark the leaf node
    for (i = 0; i<len; i++){
      index = get_index(key[i]);
      current=current->children[index];
    }
    current->end_key = false;
  }
  else if (match(t, key) && contains_prefix(t, key)){
    // If the key cotains a prefix, then delete it after the longest
    // prefix in the argument key ends.
    int longest_prefix = 0;
    for (i = 0; i<len; i++){
      index = get_index(key[i]);
      if (current->children[index]->end_key)
	longest_prefix = i;
      current = current->children[index];
    }
    // go back to the longets prefix
    current = t->head;
    for(i = 0; i<longest_prefix; i++){
      index = get_index(key[i]);
      current = current->children[index];
    }
    // remove the nodes from this point
    node_free(current);
    free(current);
    current = NULL;
  }
  else
    printf("The key does not exist. Nothing is removed\n");
}


void node_free(node * n){
  // we can only remove nodes that have no children
  for(int i = 0; i<ALPHABET_SIZE; i++){
    if (n->children[i] != NULL){
      node_free(n->children[i]);
      free(n->children[i]);
    }
  }

  // no children found; we can free memory!
  for (int j = 0; j<ALPHABET_SIZE; j++){
    if(n->children[j] == NULL) // not sure why needed, but all memory is freed!
      free(n->children[j]);
  }
}

void trie_free(trie * t){
  node * head = t->head;
  node_free(head);
  free(head);
  t->nr_words = 0;
}
