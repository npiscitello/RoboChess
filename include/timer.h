#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/* blocks for the specified number of milliseconds
 * leverages the onboard interrupt timer, albeit without interrupts
 */
void delay_ms( uint32_t time );

#endif
