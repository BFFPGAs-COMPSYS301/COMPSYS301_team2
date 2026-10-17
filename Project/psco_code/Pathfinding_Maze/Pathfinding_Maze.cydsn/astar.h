#ifndef ASTAR_H
#define ASTAR_H

#include <stdint.h>
#include <stdbool.h>


/* =========================================================
 * MAP SETTINGS
 * ========================================================= */

#define MAP_ROWS 15
#define MAP_COLS 19

#define MAX_CELLS (MAP_ROWS * MAP_COLS)

/*
 * Maximum number of checkpoints.
 *
 * This includes the START and END points.
 */
#define MAX_CHECKPOINTS 20

/*
 * Maximum number of movement commands that can
 * be stored in the complete route.
 */
#define MAX_COMMANDS 1024


/* =========================================================
 * POSITION
 * ========================================================= */

typedef struct
{
    uint8_t row;
    uint8_t col;

} Position;


/* =========================================================
 * ROBOT DIRECTION
 * ========================================================= */

typedef enum
{
    DIR_UP = 0,
    DIR_RIGHT = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 3

} Direction;


/* =========================================================
 * ROBOT COMMANDS
 *
 * Turning does NOT move the robot.
 * CMD_FORWARD moves one cell.
 * ========================================================= */

typedef enum
{
    CMD_FORWARD = 0,
    CMD_LEFT = 1,
    CMD_RIGHT = 2,
    CMD_UTURN = 3

} Command;


/* =========================================================
 * CHECKPOINTS
 *
 * points[0] = starting position
 * points[1] = checkpoint 1
 * points[2] = checkpoint 2
 * ...
 * points[count - 1] = final position
 * ========================================================= */

typedef struct
{
    Position points[MAX_CHECKPOINTS];

    uint8_t count;

} Checkpoints;


/* =========================================================
 * COMPLETE ROUTE
 * ========================================================= */

typedef struct
{
    /*
     * Complete list of robot commands.
     */
    Command commands[MAX_COMMANDS];

    /*
     * Number of commands in the route.
     */
    uint16_t length;

    /*
     * Command index at which each checkpoint
     * is reached.
     *
     * checkpointCommand[0] = starting point
     * checkpointCommand[1] = checkpoint 1
     * etc.
     */
    uint16_t checkpointCommand[MAX_CHECKPOINTS];

    /*
     * Number of checkpoints.
     */
    uint8_t checkpointCount;

    /*
     * Direction the robot is facing when
     * the route is complete.
     */
    Direction finalDirection;

} Route;


/* =========================================================
 * BUILD COMPLETE ROUTE
 *
 * Calculates the route through all checkpoints:
 *
 * Point 0 -> Point 1 -> Point 2 -> ... -> Point N
 *
 * Returns true if a route was successfully found.
 * ========================================================= */

bool AStar_BuildRoute(
    const uint8_t map[MAP_ROWS][MAP_COLS],
    const Checkpoints *checkpoints,
    Direction startingDirection,
    Route *route
);


#endif