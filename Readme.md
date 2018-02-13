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
