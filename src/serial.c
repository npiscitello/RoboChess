#include "serial.h"

// data reg
#define REG_DATA_BASE_ADDR 0x10001010
#define REG_DATA_RAVAIL_OFFSET 16
#define REG_DATA_RVALID_OFFSET 15
#define REG_DATA_PARTIY_ERROR_OFFSET 9
#define REG_DATA_DATA_OFFSET 0

// control reg
#define REG_CTRL_BASE_ADDR 0x10001014
#define REG_CTRL_WSPACE_OFFSET 16
#define REG_CTRL_WRITE_INT_OFFSET 9
#define REG_CTRL_READ_INT_OFFSET 8
#define REG_CTRL_WRITE_INT_ENABLE_OFFSET 1
#define REG_CTRL_READ_INT_ENABLE_OFFSET 0

#define _BV(bit) (1 << (bit))

int serial_read( unsigned char* data ) {
  // blah
  return -1;
}

int serial_write( unsigned char data ) {
  if( (*REG_CTRL_BASE_ADDR >> REG_CTRL_WSPACE_OFFSET) != 0 ) {
    // we can write!
  }
  return -1;
}
