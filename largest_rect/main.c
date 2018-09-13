#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int* area_around_pos(int arr[], unsigned int pos, unsigned int arr_len, int * res);

int main(){
  int arr[MAX];
  char s[MAX], *val;
  char delim[] = " \t\r\n";
  // scan line
  fgets(s, MAX, stdin);

  // split array using delimiter and strtok
  val = strtok(s, delim);

  // store the first int
  unsigned int i=0, arr_len;
  int r = sscanf(val, "%d", &arr[i]);

  // store the rest of the ints
  while(r){
    // read the next value (number)
    val = strtok(NULL, delim); // use NULL when same string is used
    // store the found number. val == NULL when the string is finished
    r = (val == NULL) ? 0 : sscanf(val, "%d", &arr[++i]);
  }
  
  arr_len = ++i;

  int max_area = -MAX;
  int *res = malloc(sizeof(int)*3);
  unsigned int left, right;
  for(i = 0; i < arr_len; i++){
    area_around_pos(arr, i, arr_len, res);
    if (res[0] > max_area){
      max_area = res[0];
      left = res[1];
      right = res[2];
    }
  }

  // print res
  printf("%d ", left);
  printf("%d", right);
  printf(": %d\n", max_area);

  free(res);
  
  return 0;
}


int* area_around_pos(int arr[], unsigned int pos, unsigned int arr_len, int * res){
  int i;
  for (i = pos -1; i >= 0 && arr[pos] <= arr[i]; i--);
  res[1] = ++i;
  for (i = pos; i < arr_len && arr[pos] <= arr[i]; i++);
  res[2] = --i;
  
  res[0] =  (res[2] - res[1] + 1)*arr[pos];

  return res;

}
