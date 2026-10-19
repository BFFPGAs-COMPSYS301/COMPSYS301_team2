#ifndef ASTAR_H
#define ASTAR_H

#include <stdint.h>
#include <stdbool.h>


// Map Settings
#define MAP_ROWS 15
#define MAP_COLS 19

#define MAX_CELLS (MAP_ROWS * MAP_COLS)

// Maximum number of checkpoints. includes the START and END points.
#define MAX_CHECKPOINTS 20

// Maximum number of movement commands that can be stored in the complete route.
#define MAX_COMMANDS 1024


// Position
typedef struct
{
    uint8_t row;
    uint8_t col;

} Position;


// Robot Direction
typedef enum
{
    DIR_UP = 0,
    DIR_RIGHT = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 3

} Direction;


typedef enum
{
    CMD_FORWARD = 0,
    CMD_LEFT = 1,
    CMD_RIGHT = 2,
    CMD_UTURN = 3,
    
    CMD_LEFT_SHORT = 4,
    CMD_RIGHT_SHORT = 5

} Command;


// CHECKPOINTS
typedef struct
{
    Position points[MAX_CHECKPOINTS];

    uint8_t count;

} Checkpoints;


// COMPLETE ROUTE
typedef struct
{
    // Complete list of robot commands.
    Command commands[MAX_COMMANDS];

    // Number of commands in the route.
    uint16_t length;

    // Command index at which each checkpoint is reached.
    uint16_t checkpointCommand[MAX_CHECKPOINTS];

    // Number of checkpoints.
    uint8_t checkpointCount;

    // Direction the robot is facing when the route is complete.
    Direction finalDirection;

} Route;


// Calculates the route through all checkpoints, returns true if a route was successfully found.
bool AStar_BuildRoute(
    const uint8_t map[MAP_ROWS][MAP_COLS],
    const Checkpoints *checkpoints,
    Direction startingDirection,
    Route *route
);


#endif