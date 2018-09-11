#include "skyline.h"

int main(){
  int buildings[8][3] = {{1, 11, 5}, {2, 6, 7}, {3, 13, 9}, 
			 {12, 7, 16}, {14, 3, 25}, {19, 18, 22}, 
			 {23, 13, 29}, {24, 4, 28}};

  city c[1];
  city_init(c);
  for (int i=0; i<8; i++){
    city_push(c, building_create(buildings[i]));
  }

  city_free(c);
  return 0;
}
