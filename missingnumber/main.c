#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_NUMBER 10000

int missing(int arr[], unsigned int len);
void print_array(int arr[], unsigned int length);

int main(){
  int arr[MAX_NUMBER];
  int r, value;
  char c;
  int i = 0;
  char delims[] = " \t\r\n";
   
  char s[MAX_NUMBER];
  fgets(s, MAX_NUMBER, stdin);
  char * val;
  val = strtok(s, delims);
  i = 0;
  r = sscanf(val, "%d", &arr[i]);

  while(r){
    i++;
    val = strtok(NULL, delims);
    r = (val == NULL) ? 0 : sscanf(val, "%d", &arr[i]);
  }
  
  
  print_array(arr, i);
  return 0;
  unsigned int len = i;
  int missing_number = missing(arr, len);
  if (missing_number)
    printf("The missing number is %d\n", missing_number);
  else
    printf("There are no missing numbers\n");
  return 0;
}

int missing(int arr[], unsigned int len){
  print_array(arr, len);
  if (len == 1)
    return arr[0];
  else if (len == 2)
    return arr[1] - arr[0] > 1 ? arr[1] - 1 : 0;
  else{
    // split up the array into two arrays
    int arr_new[len/2];
    for (int i = len - len/2; i<len; i++)
      arr_new[i-(len - len/2)] = arr[i];

    int m1 = missing(arr, len - len/2);
    
    int m2 = missing(arr_new, len/2);
    if (len)
    if (len/2 == 1)
      return m2 - arr[len -len/2 -1]  > 1 ? m2 - 1 : 0 + m1;
    
    return m1 + m2;
	
  }
     
}

void print_array(int arr[], unsigned int length){
  printf("(");
  for(unsigned int i = 0; i<length; i++){
    if(i==length-1)
      printf("%d", arr[i]);
    else
      printf("%d, ", arr[i]);
  }
  printf(")");
  printf("\n");
}
