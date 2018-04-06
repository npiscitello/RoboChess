#include "serial.h"
#include "nav.h"
#include "timer.h"

// in milliseconds, max 42949
#define DELAY 5000

int main() {
  serial_init();
  write_command(START, 0x00, 0);
  write_command(SAFE, 0x00, 0);

  location_t rotate;
  while( 1 ) {
    rotate.head = 180;
    rotate_to_heading(rotate);

    delay_ms(DELAY);

    rotate.head = 0;
    rotate_to_heading(rotate);

    delay_ms(DELAY);
  }

  return 0;
}
