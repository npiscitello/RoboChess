#include <stdio.h>

#include <stdint.h>
#include <math.h>

#include "nav.h"
#include "nios2_address_map.h"
#include "serial.h"
#include "timer.h"

/* landmark info - since the OCI works in mm, we will too
 * By cross referencing these with the current location and knowledge of the Roomba's geometry, we
 * can figure out exactly where the robot is in at least one dimension when a sensor is triggered.
 * Because this is fairly large scale, we visualize the 'board' as an area of floor bounded by walls
 * and the cells defined by gridlines, not the traditional black/white pattern (though, since we use
 * the IR sensors on the Roomba and not visible color, this pattern is not impossible to use but may
 * require some tweaking or special materials). */
// measurements from center of bounding box lines, mm
#define BOARD_CELL_SIZE_X     400
#define BOARD_CELL_SIZE_Y     400
#define BOARD_CELLS_X         8
#define BOARD_CELLS_Y         8
// width of the gridlines defining a cell, mm
#define BOARD_GRID_WIDTH      10
#define BOARD_MAX_X           (BOARD_CELLS_X * BOARD_CELL_SIZE_X)
#define BOARD_MAX_Y           (BOARD_CELLS_Y * BOARD_CELL_SIZE_Y)

// roomba geometry - linear measurements relative to center of max diameter, mm
#define PHYS_MAX_DIAMETER     348.5
// distance between wheels, which are pretty close to centered on the robot
#define PHYS_WHEEL_DIAMETER   235
// Cliff sensor locations are APPROXIMATE - need to find actual layout drawings
// R/L as if looking down at the top of the robot with the wheels on the floor
#define PHYS_L_CLIFF          (location_t){-147,55}
#define PHYS_FL_CLIFF         (location_t){-40,145}
#define PHYS_FR_CLIFF         (location_t){40,145}
#define PHYS_R_CLIFF          (location_t){147,55}

// speed constants - how fast the robot moves is certain scenarios (mm/s at the wheels)
// keep in mind, we can really only work in steps of 28.5 here (which puts us at 199.5)
// this must fit in a signed (2s complement) 16 bit integer!
#define SPEED_ROTATE 200
#define SPEED_TRANSLATE 200
#define ROTATE_CLOCKWISE -1
#define ROTATE_COUNTERCLOCKWISE 1
#define DRIVE_STRAIGHT 0x8000

// in case we need to switch from degrees
#define HALF_CIRCLE 180

// current location of the robot - assumes it starts centered in the bottom-left cell facing North
// absolute (0,0) of the board is the bottom left corner, with headings like a compass
location_t current_location = {BOARD_CELL_SIZE_X/2, BOARD_CELL_SIZE_Y/2, 0};



/* rotate the robot to a specific heading
 */
int rotate_to_heading( location_t loc ) {
  // compiler doesn't like struct members...
  location_t diff;
  diff.head = loc.head - current_location.head;
  // always turn the shortest direction
  if( diff.head > HALF_CIRCLE ) {
    diff.head = diff.head - 360;
  }

  // how long the roomba must spin at the specified speed, calculated using the linear distance (over
  // circumference) the wheels must cover (clockwise positive) and the speed at which they will spin
  // The calculation is done in fp then converted to a 32 bit unsigned int for the timer function
  // in milliseconds
  // I've tried everything I can think of to get round() to work - 
  // perhaps libmath works differently on this platform?
  uint32_t travel_time = (uint32_t)((fabs(diff.head) / 360.0) * (3.14 * PHYS_WHEEL_DIAMETER)) / (SPEED_ROTATE / 1000.0);

  // send move command
  uint8_t data_packet[4];
  data_packet[0] = ((int16_t)SPEED_ROTATE >> 8) & 0xFF;
  data_packet[1] = (int16_t)SPEED_ROTATE & 0xFF;
  // positive angle = clockwise, negative = counterclockwise
  if( diff.head > 0 ) {
    data_packet[2] = ((int16_t)ROTATE_CLOCKWISE >> 8) & 0xFF;
    data_packet[3] = (int16_t)ROTATE_CLOCKWISE & 0xFF;
  } else {
    data_packet[2] = ((int16_t)ROTATE_COUNTERCLOCKWISE >> 8) & 0xFF;
    data_packet[3] = (int16_t)ROTATE_COUNTERCLOCKWISE & 0xFF;
  }
  write_command(DRIVE, data_packet, 4);

  // wait for the robot to turn around
  delay_ms(travel_time);

  // send stop command (drive at 0 speed)
  data_packet[0] = 0x00; data_packet[1] = 0x00;
  write_command(DRIVE, data_packet, 4);

  return 0;
}



/* the robot will move in a straight line to the destination
 */
int go_to_location( location_t loc ) {
  // calculate a location diff, making sure we're not going off the board
  location_t diff;
  if( loc.x < PHYS_MAX_DIAMETER / 2 ) {
    diff.x = loc.x - current_location.x;
  } else if( loc.x > BOARD_MAX_X - (PHYS_MAX_DIAMETER / 2) ) {
    diff.x = (BOARD_MAX_X - (PHYS_MAX_DIAMETER / 2)) - current_location.x;
  } else {
    diff.x = (PHYS_MAX_DIAMETER / 2) - current_location.x;
  }

  if( loc.y < PHYS_MAX_DIAMETER / 2 ) {
    diff.y = loc.y - current_location.y;
  } else if( loc.y > BOARD_MAX_Y - (PHYS_MAX_DIAMETER / 2) ) {
    diff.y = (BOARD_MAX_Y - (PHYS_MAX_DIAMETER / 2)) - current_location.y;
  } else {
    diff.y = (PHYS_MAX_DIAMETER / 2) - current_location.y;
  }

  // calculate dead reckoning data
  int heading = arctan(diff.y / diff.x);
  int distance = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

  // move to point
  location_t rotate = {0, 0, heading};
  rotate_to_heading(rotate);

  // start moving
  uint8_t data_packet[4];
  data_packet[0] = ((int16_t)SPEED_TRANSLATE >> 8) & 0xFF;
  data_packet[1] = (int16_t)SPEED_TRANSLATE & 0xFF;
  data_packet[2] = ((int16_t)DRIVE_STRAIGHT >> 8) & 0xFF;
  data_packet[3] = (int16_t)DRIVE_STRAIGHT & 0xFF;
  write_command(DRIVE, data_packet, 4);

  uint32_t travel_time = (uint32_t)((distance / 360.0) * (3.14 * PHYS_WHEEL_DIAMETER)) / (SPEED_TRANSLATE / 1000.0);
  delay_ms(travel_time);

  // send stop command (drive at 0 speed)
  data_packet[0] = 0x00; data_packet[1] = 0x00;
  write_command(DRIVE, data_packet, 4);

  return(0);
}
