typedef struct building_t{
  unsigned int ht;
  int left, right;

  struct building_t * next;
} building;

typedef struct city_t{
  struct  building_t * head;
  unsigned int length;
} city;

typedef struct skyline_t{
  int (* data)[2];
  unsigned int length;
} skyline;

void city_init(city * c);
void city_push(city * c, building * b);
void city_merge(city * c, city * c2);
city * city_split(city * c, city * c2);
void city_print(city * c);
building * building_create(int data[3]);
void city_free(city * c);
void skyline_free(skyline * s);
skyline * find_skyline(city * c);
void skyline_print(skyline * s);
// need to create a skyline data type, and additional functions assumed in
// find_skyline

// (0, 2)(3, 4)  (2,3) (4,0) -> (0,2) (2,3) (3,4)(4,0)
// (1,2)(3,3)    (2,6) (5,0) -> (1,2)(2,6)(5,0)
// (0,1)(2,3)   (3,2)(5,2) -> (0,1)(2,3)(3,2)(5,2)
