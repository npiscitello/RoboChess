#ifndef NAV__H
#define NAV__H

// container for location data
struct location {
  float x;
  float y;
  float head;
};
typedef struct location location_t;

/* blocking - center the roomba on a specific location at a specific heading
 *  loc: the location and heading to drive to
 *
 *  returns: a code indicating the success of the operation
 *    1 - the robot could not get to the location
 *    0 - the location has been reached
 */
int go_to_location( location_t loc );

#endif
