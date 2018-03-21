#ifndef NAV__H
#define NAV__H

// container for location data
struct location {
  float x;
  float y;
  // compass directions - 0 is N, 90 is E, etc.
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

/* blocking - rotate the roomba in place to the specified heading
 *  loc: defines the heading to which the robot is rotating
 *
 *  returns: a code indicating the success of the operation
 *    1 - the robot could not rotate to the heading
 *    0 - the heading has been reached
 */
int rotate_to_heading( location_t loc );

#endif
