#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

/* read one byte from the UART receive FIFO
 *  data: address at which to place the read data
 *
 *  returns: a code indicating the success of the operation
 *      1   - operation completed successfully, queue contents remain
 *      0   - operation completed successfully, queue empty
 *      -1  - operation unsuccessful; queue is already empty
 */
int serial_read( uint8_t* data );

/* write one byte to the UART send FIFO
 *  data: data to push onto the queue
 *
 *  returns: a code indicating the success of the operation
 *      1   - operation completed successfully, space remaining in queue
 *      0   - operation completed successfully, queue full
 *      -1  - operation unsuccessful; queue is already full
 */
int serial_write( uint8_t data );

#endif
