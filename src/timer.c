#include "timer.h"
#include "nios2_address_map.h"

// in Hz
#define CPU_FREQ 50000000

// blocking
void delay_ms(uint32_t time) {
  // divide by 1000 b/c we're working with milliseconds, we have 1/1000 the number of cycles per
  // millisecond than cycles per second
  uint32_t num_cycles = time * (CPU_FREQ / 1000);
  *(INTERVAL_TIMER_START_LO) = num_cycles & 0xFFFF;
  *(INTERVAL_TIMER_START_HI) = (num_cycles >> 16) & 0xFFFF;

  // STOP = 0, START = 1, CONT = 0, ITR = 1
  // start the countdown, do not repeat
  *(INTERVAL_TIMER_CONTROL) = 0x0005;

  // poll the timer until done; this could be interrupt-driven but... that'll come later if needed
  while ( *(INTERVAL_TIMER_STATUS) & 0x0001 ) {}

}
