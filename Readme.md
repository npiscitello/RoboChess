# What does it do?
This project is using the robust iRobot Create platform to navigate around a chessboard.
Specifically, the goal is to be able to move to any arbitrary square from any other as determined by
a chess engine.

# Navigation Approach
This project will use fairly low-tech methods to help the robot navigate around the chessboard.
Using the optical bump sensors and low physical walls (or perhaps the iRobot Virtual Walls), we can
define the extents of the chessboard. Then, if we draw the grid using a material with some degree of
IR absorption, we can use the difference between gridlines and floor to locate the robot more
precisely than dead reckoning alone.

The approach to cohesive navigation will be twofold: the robot will hold a map of the chessboard
annotated with gridlines and cell locations in memory. Navigation around this map will be done using
dead reckoning; after receiving a command, the robot will calculate some path to complete that
command. As it traverses the path, it will estimate it's location on the map. The data from the
cliff and optical bump sensors will be used to refine this estimation, ensuring any errors
introduced from the dead reckoning don't become severe enough to impact operation.

# Target
~~This project will target an embedded Linux board (e.g. Raspberry Pi) for now but may switch
platforms in the future. This choice of platform is to allow the control and chess engine to all run
locally; using a microcontroller to connect back to a host running the chess engine and possibly
navigational code may be more desirable in the future.~~
Per instructor requirement, this project will target an Altera DE-0 board. This may make running the
chess engine locally impractical - we'll cross that bridge when we get to it. The UART interface for
the Media Computer configuration seems to be hardwired to an RS232 chip on the board; we'll need to
implement soft UART or just convert the RS232. I plan on leveraging the prebuilt UART interface; in
addition to making the software simpler, it also allows the use of standard RS232/UART conversion
equipment (instead of creating our own cables). Since the default serial settings aren't quite
right, we're going to be building a custom image based off the Basic Computer for the FPGA.
