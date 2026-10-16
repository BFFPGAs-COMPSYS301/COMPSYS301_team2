
#include "project.h"
#include "astar.h"
#include "movements.c"

#define STARTDIRECTION DIR_DOWN

const char *mazeInput[MAP_ROWS] =
{
    "1111111111111111111",
    "1010001000001000001",
    "1011101011101011101",
    "1000100000100000101",
    "1110111111111111101",
    "1010000010000000001",
    "1011111010111111101",
    "1000001000100000101",
    "1010101111101110101",
    "1010101000101010101",
    "1110101010101010101",
    "1000101010001010101",
    "1011111011111010101",
    "1000000000000010001",
    "1111111111111111111"
};


// NUMERICAL MAP This is automatically created from mazeInput.
uint8_t map[MAP_ROWS][MAP_COLS];


/* =========================================================
 * CHECKPOINTS
 *
 * IMPORTANT:
 *
 * Coordinates are ZERO-BASED.
 *
 * Top-left cell = {0,0}
 *
 * The order here is the order the robot will visit.
 *
 * points[0] MUST be the starting position.
 * The final point is the final destination.
 * ========================================================= */

Checkpoints checkpoints =
{
    .points =
    {
        {1, 1},     /* START */
        {3, 3},
        {3, 5}    /* END */
    },

    .count = 3
};


// COMPLETE ROUTE
Route route;


// ROBOT STATE
uint16_t commandIndex = 0;


// The next checkpoint the robot needs to reach. Checkpoint 0 is the starting position, so we begin waiting for checkpoint 1.
uint8_t nextCheckpoint = 1;


// Convert map to numeric map
void LoadMap(void)
{
    for (uint8_t row = 0;
         row < MAP_ROWS;
         row++)
    {
        for (uint8_t col = 0;
             col < MAP_COLS;
             col++)
        {
            map[row][col] =
                (uint8_t)(mazeInput[row][col] - '0');
        }
    }
}


// Build the complete route
bool BuildRoute(void)
{
    LoadMap();


    return AStar_BuildRoute(
        map,
        &checkpoints,
        STARTDIRECTION,
        &route
    );
}


void ExecuteNextCommand(void)
{
    Command command;
    Command nextCommand;

    // Check If we have reached the end
    if (commandIndex >= route.length)
    {
        //Robot has reached the final point. Add whatever you want to happen here.
        return;
    }

    // Get next command.
    command = route.commands[commandIndex];
    if (commandIndex + 1 < route.length) {
        nextCommand = route.commands[commandIndex + 1];
    } else {
        nextCommand = CMD_FORWARD; // No next command; use normal one-cell movement.
    }
        

    // Execute it.
    switch (command)
    {
        case CMD_FORWARD:
            // Move forward exactly one cell.
            MoveForwardOneCell(nextCommand);

            break;


        case CMD_LEFT:
            // Turn left only. Do NOT move forward.
            TurnLeft();

            break;


        case CMD_RIGHT:
            // Turn right only. Do NOT move forward.
            TurnRight();

            break;
    }


    // The command has now been executed.
    commandIndex++;


    // CHECKPOINT
    if (nextCheckpoint <
        route.checkpointCount)
    {
        if (commandIndex >=
            route.checkpointCommand[nextCheckpoint])
        {
            // The robot has reached the checkpoint. Wait 2 seconds.
            CyDelay(2000);


            // Move to next checkpoint.
            nextCheckpoint++;
        }
    }
}


int main(void)
{
    PWM_1_Start();
    PWM_2_Start();
    
    Timeout_1_Start();
    Timeout_2_Start();
    Timeout_3_Start();
    Timeout_4_Start();
    Timeout_5_Start();
    
    QuadDec_1_Start();
    
    VDAC8_1_Start();

    if (!BuildRoute())
    {

        while (1)
        {
            // Error state.
        }
    }


    // Route has now been calculated. Start robot movement.
    while (1)
    {
        ExecuteNextCommand();
    }


    return 0;
}