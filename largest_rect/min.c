// find min value of an array using binsearch

#define INF 10000000
#ifdef BIN
int min(int * arr[], unsigned int len, unsigned int start, unsigned int end){
  if (len == 1)
    return start; // or end, it dosen't matter!
  else if (len == 2)
    return (*arr)[start] <= (*arr)[end] ? start : end;
  else {
    int pos1 = min(arr, len - len/2, start, end - len/2);
    int pos2 = min(arr, len/2, start + len/2, end);
    return (*arr)[pos1] <= (*arr)[pos2] ? pos1 : pos2;
  }
}
#else

int min(int arr[], unsigned int len){
  int curr_min=INF;
  unsigned int pos=0;
  for (unsigned int i=0; i<len; i++)
    if (arr[i] < curr_min){
      curr_min = arr[i];
      pos = i;
    }

  return pos;
}

#endif

