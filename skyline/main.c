#include "skyline.h"
#include <stdio.h>

int main(){
  int buildings[8][3] = {{1, 11, 5}, {2, 6, 7}, {3, 13, 9}, 
			 {12, 7, 16}, {14, 3, 25}, {19, 18, 22}, 
			 {23, 13, 29}, {24, 4, 28}};

  city c[1];
  city_init(c);
  for (int i=7; i>=0; i--){
    city_push(c, building_create(buildings[i]));
  }
city_print(c);
#ifdef DEBUG
  
  printf("sizeof(building) = %lu\n", sizeof(building));
  
#endif
  skyline * skyline = find_skyline(c);
  skyline_print(skyline);

  skyline_free(skyline);
  

  return 0;
}
