#ifndef NAV__H
#define NAV__H

// container for location data
struct location {
  float x;
  float y;
};
typedef struct location location_t;

// test function - just prints out the values of the macros
void print_stuff(void);

#endif
