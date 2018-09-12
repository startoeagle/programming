typedef struct building_t{
  unsigned int ht;
  int left, right;

  struct building_t * next;
} building;

typedef struct city_t{
  struct  building_t * head;
  unsigned int length;
} city;

void city_init(city * c);
void city_push(city * c, building * b);
void city_merge(city * c, city * c2);
building * building_create(int data[3]);
void city_free(city * c);

// need to create a skyline data type, and additional functions assumed in
// find_skyline

