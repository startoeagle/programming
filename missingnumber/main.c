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
  if (missing_number)
    printf("The missing number is %d\n", missing_number);
  else
    printf("There are no missing numbers\n");
  return 0;
}

int missing(int arr[], unsigned int len){
  printf("(");
  for(int i=0; i<len; i++){
    printf("%d ", arr[i]);
  }
  printf(")");
  printf("\n");
  if (len == 1)
    return arr[0];
  else if (len == 2)
    return arr[1] - arr[0] > 1 ? arr[1] - 1 : 0;
  else{
    // split up the array into two arrays
    int arr_new[len/2];
    for (int i = len/2; i<len; i++)
      arr_new[i-len/2] = arr[i];

    int m1 = missing(arr, len - len/2);
    printf("m1 = %d\n", m1);
    printf("m2 = %d\n", m2);
    int m2 = missing(arr_new, len/2);
    if(len/2 == 1)
      // int this case we need to check if the missing number
      // is between the two subarrays
      return arr[len-len/2-1] - m2 > 1 ? m2 - 1 : 0 + m1;
    else
      return m1 + m2;
	
  }
     
}
