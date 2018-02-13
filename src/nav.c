#include <stdio.h>

#include "nav.h"

// most accurate current location of the robot
location_t current_location = {0,0};

/* landmark info - since the OCI works in mm, we will too
 * By cross referencing these with the current location and knowledge of the Roomba's geometry, we
 * can figure out exactly where the robot is in at least one dimension when a sensor is triggered.
 * Because this is fairly large scale, we visualize the 'board' as an area of floor bounded by walls
 * and the cells defined by gridlines, not the traditional black/white pattern (though, since we use
 * the IR sensors on the Roomba and not visible color, this pattern is not impossible to use but may
 * require some tweaking or special materials). */
#define BOARD_CELL_SIZE_X     400
#define BOARD_CELL_SIZE_Y     400
#define BOARD_CELLS_X         8
#define BOARD_CELLS_Y         8
// width of the gridlines defining a cell, mm
#define BOARD_GRID_WIDTH      10
#define BOARD_MAX_X           (BOARD_CELLS_X * BOARD_CELL_SIZE_X)
#define BOARD_MAX_Y           (BOARD_CELLS_Y * BOARD_CELL_SIZE_Y)

/* roomba geometry - linear measurements relative to center of max diameter */
#define PHYS_MAX_DIAMETER     348.5
// Cliff sensor locations are APPROXIMATE - need to find actual layout drawings
// R/L as if looking down at the top of the robot with the wheels on the floor
#define PHYS_L_CLIFF (location_t){-147,55}
#define PHYS_FL_CLIFF = (location_t){-40,145}
#define PHYS_FR_CLIFF = (location_t){40,145}
#define PHYS_R_CLIFF = (location_t){147,55}

void print_stuff(void) {
  printf("Board constants - cell_size_x: %d, cell_size_y: %d, cells_x: %d, cells_y: %d, grid_width: %d, max_x: %d, max_y: %d\n", 
      BOARD_CELL_SIZE_X, BOARD_CELL_SIZE_Y, BOARD_CELLS_X, BOARD_CELLS_Y, BOARD_GRID_WIDTH, BOARD_MAX_X, BOARD_MAX_Y);
  printf("Physcial constants - max_diameter: %f, l_cliff_x: %f, l_cliff_y: %f\n", 
      PHYS_MAX_DIAMETER, PHYS_L_CLIFF.x, PHYS_L_CLIFF.y);

  return;
}
