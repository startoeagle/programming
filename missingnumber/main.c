#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NUMBER 10000

int missing(int arr[], unsigned int len);
int main(){
  int arr[MAX_NUMBER];
  int r;
  char c;
  int i = 0;
  r = scanf("%c", &c);
  while(r){
    if (c == '\n')
      break;
    else if (isdigit(c)){
      arr[i] = (int) c -'0';
      i++;
    }
    r = scanf("%c", &c);
  }
  unsigned int len = i;
  int missing_number = missing(arr, len);
  printf("The missing number is %d\n", missing_number);
  return 0;
}

int missing(int arr[], unsigned int len){
  if (len == 1)
    return 0; // There are no missing integers in this subarray
  else if (len == 2)
    return arr[1] - arr[0] > 1 ? arr[1] - 1 : 0;
  else{
    // split up the array into two arrays
    int arr_new[len/2];
    for (int i = len/2; i<len; i++)
      arr_new[i-len/2] = arr[i];
    return missing(arr, len - len/2) + missing(arr_new, len/2);
  }
     
}
