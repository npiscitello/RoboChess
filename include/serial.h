#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

enum command {
// COMMAND            = OPC, // <DATA BYTES> DESCRIPTION
  // Getting Started Commands //
  START               = 128, // <0> starts Open Interface, robot will respond to commands. Passive mode.
  RESET               = 7,   // <0> simulated hard reset (remove/reinsert battery)
  STOP                = 173, // <0> stops Open Interface, robot will not respond to commands
  BAUD                = 129, // <1> sets baud rate; consult manual for table

  // Mode Commands //
  SAFE                = 131, // <0> allows full control with safety interlocks
  CONTROL             = 130, // <0> same as SAFE commands (OPC 131)
  FULL                = 132, // <0> allows full control with no safety interlocks

  // Cleaning Commands //
  CLEAN               = 135, // <0> start a default cleaning mode, pauses if there's a clean in progress
  MAX_CLEAN           = 136, // <0> start a Max cleaning mode, pauses if there's a clean in progress
  SPOT                = 134, // <0> start a spot cleaning mode, pasuses if there's a clean in progress
  FORCE_SEEK_DOCK     = 143, // <0> have the roomba dock itself the next time it sees one
  POWER               = 133, // <0> soft power down
  SCHEDULE            = 167, // <15> set a schedule; to disable, send all zeroes
  SET_DAY_TIME        = 168, // <3> set the internal clock

  // Actuator Commands //
  DRIVE               = 137, // <4> set average wheel velocity and turn radius
  DRIVE_DIRECT        = 145, // <4> set the velocity of each wheel independently
  DRIVE_PWM           = 146, // <4> set the PWM value of each wheel motor
  MOTORS              = 138, // <1> binary control of aux motors
  PWM_MOTORS          = 144, // <3> velocity control of aux motors
  LEDS                = 139, // <3> control the LEDs on the top of the robot
  SCHEDULING_LEDS     = 162, // <2> control the scheduling LEDs on higher models
  DIGIT_LEDS_RAW      = 163, // <4> control individual segments on the SSDs
  BUTTONS_CMD         = 165, // <1> "This command lets you push Roomba's buttons"
  DIGIT_LEDS_ASCII    = 164, // <4> control the SSDs using a subset of the ASCII characters
  SONG                = 140, // <2*(# notes)+2> specify up to 4 songs to be played on command
  PLAY                = 141, // <1> play a song previously defined with SONG (OPC 140)

  // Input Commands //
  QUERY_SENSOR        = 142, // <1> request a sensor data packet
  QUERY_LIST          = 149, // <(# packets)+1> request multiple sensor packets in specified order
  STREAM              = 148, // <(# packets)+1> request sensor data to be sent every 15ms
  CTRL_STREAM         = 150  // <1> pause/resume stream without clearing request
};

enum sensor {
//PACKET NAME         = ID,  // <DATA BYTES> DESCRIPTION
  // Packet Groups //
  GROUP_0             = 0,   // <26> packets 7-26
  GROUP_1             = 1,   // <10> packets 7-16
  GROUP_2             = 2,   // <6> packets 17-20
  GROUP_3             = 3,   // <10> packets 21-26
  GROUP_4             = 4,   // <14> packets 27-34
  GROUP_5             = 5,   // <12> packets 35-42
  GROUP_6             = 6,   // <52> packets 7-42
  GROUP_100           = 100, // <80> packets 7-58
  GROUP_101           = 101, // <28> packets 43-58
  GROUP_106           = 106, // <12> packets 46-51
  GROUP_107           = 107, // <9> packets 54-58

  // Individual Packets //
  BUMP_WHEEL_DROP       = 7,   // <1> bitmask for wheel drop sensors and bumpers
  CLIFF_LEFT            = 9,   // <1> left side cliff sensor, binary version of ID28
  CLIFF_FRONT_LEFT      = 10,  // <1> front left cliff sensor, binary version of ID29
  CLIFF_FRONT_RIGHT     = 11,  // <1> front right cliff sensor, binary version of ID30
  CLIFF_RIGHT           = 12,  // <1> right side cliff sensor, binary version of ID31
  VIRTUAL_WALL          = 13,  // <1> state of the virtual wall detector
  WHEEL_OVERCURRENT     = 14,  // <1> motor overcurrent sensors (no sensor for main vacuum)
  DIRT_DETECT           = 15,  // <1> level of the dirt detect sensor
  UNUSED_BYTE           = 16,  // <1> always 0, sent after ID15 when request is 0, 1, or 6
  IR_CHAR_OMNI          = 17,  // <1> IR code being received; 0 means nothing is being received
  IR_CHAR_LEFT          = 52,  // <1> IR code being received on the left
  IR_CHAR_RIGHT         = 53,  // <1> IR code being received on the right
  BUTTONS_SENSOR        = 18,  // <1> state of the buttons on the top of the robot
  DISTANCE              = 19,  // <2> distance traveled since this packet was last requested, mm
  ANGLE                 = 20,  // <2> angle rotated since this packet was last requested, degrees
  CHARGING              = 21,  // <1> charging state
  BAT_VOLTAGE           = 22,  // <2> voltage of the internal battery, mV
  BAT_CURRENT           = 23,  // <2> current flowing out of (-) or into (+) the battery
  BAT_TEMPERATURE       = 24,  // <1> battery temperature, Celsius
  BAT_CHARGE            = 25,  // <2> estimated mAh capacity
  CLIFF_LEFT_SIG        = 28,  // <2> strength of left side cliff sensor
  CLIFF_FRONT_LEFT_SIG  = 29,  // <2> strength of front left cliff sensor
  CLIFF_FRONT_RIGHT_SIG = 30,  // <2> strength of front right cliff sensor
  CLIFF_RIGHT_SIG       = 31,  // <2> strength of right side cliff sensor
  CHARGING_AVAIL        = 34,  // <1> information about charging status
  OI_MODE               = 35,  // <1> which mode the Roomba is in
  SONG_NUMBER           = 36,  // <1> which song is currently selected
  SONG_PLAYING          = 37,  // <1> returns whether a song is playing or not
  NUM_STREAM_PACKETS    = 38,  // <1> how many packets are being streamed
  REQUESTED_VELO        = 39,  // <2> velocity most recently requested by a drive command
  REQUESTED_RADIUS      = 40,  // <2> radius most recently requested - broken before FW3.3.0
  REQUESTED_VELO_RIGHT  = 41,  // <2> right wheel velocity most recently requested
  REQUESTED_VELO_LEFT   = 42,  // <2> left wheel velocity most recently requested
  ENCODER_COUNT_LEFT    = 43,  // <2> cumulative enocder count, left wheel
  ENCODER_COUNT_RIGHT   = 44,  // <2> cumulative encoder count, right wheel
  BUMP                  = 45,  // <1> light bumper bitmask, binary version of ID46-51
  BUMP_LEFT_SIG         = 46,  // <2> left light bumper strength
  BUMP_FRONT_LEFT_SIG   = 47,  // <2> front left light bumper strength
  BUMP_CENTER_LEFT_SIG  = 48,  // <2> center left light bumper strength
  BUMP_CENTER_RIGHT_SIG = 49,  // <2> center right light bumper strength
  BUMP_FRONT_RIGHT_SIG  = 50,  // <2> front right light bumper strength
  BUMP_RIGHT_SIG        = 51,  // <2> right light bumper strength
  MOTOR_CURRENT_LEFT    = 54,  // <2> the current being drawn by the left motor
  MOTOR_CURRENT_RIGHT   = 55,  // <2> the current being drawn by the right motor
  MOTOR_CURRENT_MAIN    = 56,  // <2> the current being drawn by the main brush motor
  MOTOR_CURRENT_SIDE    = 57,  // <2> the current being drawn by the side brush
  STASIS                = 58   // <1> status of the stasis sensor
};

/* set up the serial interface
 */
void serial_init();

/* send a command to the Roomba
 *
 */
void write_command( uint8_t opcode, uint8_t* data, uint8_t data_len );

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
