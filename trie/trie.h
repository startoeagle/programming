
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct node_t{
  struct node_t * children[ALPHABET_SIZE];
  bool end_key;
} node;
typedef struct trie_t{
  node * head;
  unsigned int nr_words;
} trie;
bool search(trie * t, char key[]);
void trie_init(trie * t);
void insert(trie * t, char key[]);
void trie_free(trie * t);
void node_free(node * n);
void node_remove(trie * t, char key[]);
