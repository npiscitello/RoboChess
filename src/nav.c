#include <stdio.h>

#include "nav.h"

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
#define SPEED_ROTATE 50
#define SPEED_TRANSLATE 50

// current location of the robot - assumes it starts centered in the bottom-left cell facing North
// absolute (0,0) of the board is the bottom left corner, with headings like a compass
location_t current_location = {BOARD_CELL_SIZE_X/2, BOARD_CELL_SIZE_Y/2, 0};



/* rotate the robot to a specific heading
 */
int rotate_to_heading( location_t loc ) {
  location_t diff;
  diff.head = loc.head - current_location.head;


  return 0;
}



/* the strategy here is to move like a cartesian robot, finding the x position then going to the y.
 * This is certainly not the most efficient way to do this, but its a good start
 */
int go_to_location( location_t loc ) {
  // calculate a location diff
  location_t diff;
  diff.x = loc.x - current_location.x;
  diff.y = loc.y - current_location.y;

  // move in X
  return(0);
}
