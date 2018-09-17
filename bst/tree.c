#include "tree.h"


tree *  tree_init(){
  tree * t = (tree *) malloc(sizeof(tree));
  t->head = NULL;
  return t;
}


node * node_init(){
  node * n;
  n = (node *) malloc(sizeof(node));
  n->left = NULL;
  n->right = NULL;
  return n;
}

#ifndef ITER
void node_free(node * n){
  // frees all nodes below n
  
  
  if(n->right != NULL)
    node_free(n->right);

  n->right = NULL;
  
  if(n->left != NULL)
    node_free(n->left);

  n->left = NULL;

  if (n->right == NULL && n->left == NULL){
    free(n);
    n = NULL;
  }

}
#endif

void tree_free(tree * t){
  node * head = t->head;
  // a recursicve approac is simpler and wont requiere any back track
  // an iterative process is nicer.
  node_free(head);
  free(t);
  t = NULL;
}

void node_print(node * n){
  if (n->left != NULL)
    node_print(n->left);
  
  printf("%d ", n->val);
  
  if (n->right != NULL)
    node_print(n->right);
}
void tree_print(tree * t){
  node * head = t->head;
  node_print(head);
  printf("\n");
}
unsigned int tree_depth(node * n){
  // calculates the node depth from the subtree created from node n
  unsigned int res,left,right;
  left = right = 0;
  if (n == NULL)
    return 0;

  res = 1;
  if (n->left != NULL || n->right != NULL)
    // use this extra if-cluase to make sure the depth res is only
    // increased by one
    res++;
    
  if (n->left != NULL)
    left = tree_depth(n->left);
  
  if (n->right != NULL)
    right = tree_depth(n->right);

  return res + left + right;
}

int is_unbalanced(node * n){
  if (n == NULL)
    return 0;
  int res =  tree_depth(n->right) - tree_depth(n->left);
    
  return abs(res) > 1 ? res : 0;
}

node * right_rotate(node * n){
#ifdef DB
  printf("in right rotate\n");
#endif
  // save the right subtree of n->eft
  node * left_right = n->left->right;

  // let left child be parent of n
  node * old_root = n; // store the old root in old_root
  n = n->left;

  // update the new root
  old_root->left = left_right;
  n->right = old_root;


  return n;
}

node * left_rotate(node * n){
#ifdef DB
  printf("in left rotate\n");
#endif

  // save right left child of n
  node * right_left = n->right->left;

  // save the old root
  node * old_root = n;

  // move so that the root of the subtree is the right child of
  // argument node
  n = n->right;

  // move the pointers
  old_root->right = right_left;
  n->left = old_root;

  return n;
}

 

void insert(tree * t, int val){
  if(t->head == NULL){
    t->head = node_init();
    t->head->val = val;
    return;
  }
  node * head = t->head;
  while(1){
   
    if (head->left != NULL && head->val > val){
      // go to left
      head = head->left;
    }
    else if (head->right != NULL && head->val <= val){
      head = head->right;
    }
    else if (head->left == NULL && head->val > val){
      // go to left
      head->left = node_init();
      head->left->val = val;
      break;
    }
    else if (head->right == NULL && head->val <= val){
      head->right = node_init();
      head->right->val = val;
      break;
    }
  }


  /*
    BALANCE THE TREE
  */
  
  // find the unbalanced node
  // follow the path of the inserted value to do this
  head = t->head;
  node * prev = NULL;
  int is_unb;
  int left, right;

  while(head != NULL){
    // Find which direction the unbalancing occurs
    is_unb = is_unbalanced(head);
    if (is_unb < 0){
      // the subtree is unbalanced node is unbalanced to the left
      // check tree deapth of the grand childs
      left = tree_depth(head->left->left);
      right = tree_depth(head->left->right);
      if (left > right)
	head = right_rotate(head);
      else if (left < right){
	head->left = left_rotate(head->left);
	head  = right_rotate(head);
      }


      
      if (prev != NULL)
	prev->left = head;
      else
	t->head = head;

      break;
    }
    else if (is_unb > 0){
      left = tree_depth(head->right->left);
      right = tree_depth(head->right->right);

      if (right > left)
	head = left_rotate(head);
      else if(right < left){
	head->right = right_rotate(head->right);
	head  = left_rotate(head);
      }

      // make sure that the tree follows the changes caused by the
      // rotation
      if (prev != NULL)
	prev->right = head;
      else
	t->head = head;
      
      

      break;
    
    }
    else if(!is_unb && head->left == NULL && head->right == NULL)
      // nothing to do, the tree is balanced after insert
      return;
    
    else if (val < head->val){
      // continue
      prev = head;
      head = head->left;
    }
    
    else if (val >= head->val){
      prev = head;
      head = head->right;
    }
      
    
  }
  
}


