#include <stdio.h>
#include <string.h> // strlen
#include <stdlib.h>
int is_pal(char * s, unsigned int len_s){
  for (int i = 0; i < len_s/2; i++){
    if(s[len_s -1 - i] != s[i])
      return 0;
  }
  return 1;
}

void print_substring(char * s, unsigned int len){
  for (int i = 0; i<len; i++){
    printf("%c", *(s+i));
  }
}


int main(){
  int n; // number of strings
  char strings[1000][100]; // the different strings
  char *s; // temp string
  int r = scanf("%d", &n);
  int i,j,len;
  while(r==1 && r != EOF){
    // read the strings
   
    for (i = 0; i < n; i++) {
      // use scanf to store a string
      scanf("%s", strings[i]);
    }

#if DEBUG
    printf("Got the strings: \n");
    for (i = 0; i < n; i++){
      printf("%s\n", strings[i]);

      if (is_pal(strings[i], 3))
	printf("%s is a palindrome\n", strings[i]);
      else
	printf("%s is not a palindrome\n", strings[i]);
    }
#endif

    // main problem solving
    for (i=0; i < n; i++){
      s = strdup(strings[i]);
      // start at substring length of 3, since 1 and 2 are trivial
      for (j=0; j<strlen(s); j++){
	for (len = 3 ;len<=strlen(s)-j; len++){
	  if (is_pal(s+j, len)){
	    print_substring(s+j, len);
	    printf(" is a palindrome\n");
	  }
	}
      }
    }
    r = scanf("%d", &n);
  }

  free(s);
  return 0;
}

  /*
  Given a string S, find the longest palindromic substring in S.

Substring of string S:

S[ i . . . . j ] where 0 ≤ i ≤ j < len(S)

Palindrome string:

A string which reads the same backwards. More formally, S is palindrome if reverse(S) = S.

Incase of conflict, return the substring which occurs first ( with the least starting index ).

NOTE: Required Time Complexity O(n2).

Input:

The first line of input consists number of the test cases. The following T lines consist of a string each.


Output:

In each separate line print the longest palindrome of the string given in the respective test case.


Constraints:

1 ≤T≤ 100
1 ≤ Str Length≤ 104

Example:

Input:
1
aaaabbaa

Output:

aabbaa


										    */
