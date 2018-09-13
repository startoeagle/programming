// This is an alternative solution using divide and conquer

#include <stdio.h>
#include <string.h>
#include "min.h"

#define MAX 100
int max_area(int arr[], unsigned int len);
int main(){
  // store the histogram as an int array
  int arr[MAX];
  
  // read the in stream!
  char s[MAX];
  // read the line as a string
  fgets(s, MAX, stdin);

  // split the string
  char delim[]=" \n", *val;
  val = strtok(s, delim);

  // stor the first value
  unsigned int i = 0;
  int r = sscanf(val, "%d", &arr[i++]);
  while(r){
    val = strtok(NULL, delim);
    if(val == NULL)
      break;
    else
      r = sscanf(val, "%d", &arr[i++]);
  }

  printf("%d\n", max_area(arr, i));
  
  return 0;
}


int max_area(int arr[], unsigned int len){
  if(len == 0)
    return 0;
  else if(len == 1)
    return arr[0];
  else {
#ifdef BIN
    int min_pos = min(&arr, len, 0, len-1);
    printf("min at %d and is equal to %d\n", min_pos, arr[min_pos]);
#else
    int min_pos = min(arr, len);
#endif
    int arr_new[len - min_pos - 1];
    for(unsigned int i = 0; i<len - min_pos - 1; i++)
      arr_new[i] = arr[min_pos+1+i];
    int area1 = max_area(arr, min_pos);
    int area2 = max_area(arr_new, len - min_pos -1);
    if (area1 > area2 && area1 > arr[min_pos]*len)
      return area1;
    else if (area1 < area2 && area2 > arr[min_pos]*len)
      return area2;
    else
      return arr[min_pos]*len;
  }
  
}
