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

// makes the registers easy to use; we don't have to manually cast them every time
// these could probably be real macros, buuuut something something premature optimization
volatile uint32_t* REG_DATA_PTR = (uint32_t*) REG_DATA_BASE_ADDR;
volatile uint32_t* REG_CTRL_PTR = (uint32_t*) REG_CTRL_BASE_ADDR;

int serial_read( uint8_t* data ) {
  // blah
  return -1;
}

int serial_write( uint8_t data ) {
  // is there space in the write FIFO?
  if( (*REG_CTRL_PTR >> REG_CTRL_WSPACE_OFFSET) > 0 ) {
    *REG_DATA_PTR |= (uint32_t)data << REG_DATA_DATA_OFFSET;
  } else {
    return -1;
  }

  // we wrote; is there still space?
  if( (*REG_CTRL_PTR >> REG_CTRL_WSPACE_OFFSET) > 0 ) {
    return 1;
  } else {
    return 0;
  }
}
