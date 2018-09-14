#include "trie.h"
#include <stdio.h>

int main(){
  char strings[][256] = {"anton", "karlsson"};

  trie t[1];
  trie_init(t);
  for (int i=0; i<2; i++)
    insert(t, strings[i]);


  search(t, "anton");
  search(t, "an");
  search(t, "ton");

  search(t, "karl");
  search(t, "karlsson");
  search(t, "son");

  node_remove(t, "anton");
  search(t, "anton");
  
  search(t, "anto");

  search(t, "karlsson");

  trie_free(t);
  return 0;
}
