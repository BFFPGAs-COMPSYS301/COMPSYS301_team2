
#include "project.h"
#include "astar.h"
#include "movements.c"

#define STARTDIRECTION DIR_RIGHT

const char *mazeInput[MAP_ROWS] =
{
    "1111100011111111111",
    "1000100010010001001",
    "1111111010011011111",
    "1010101111011110001",
    "1111100001001010000",
    "0100101111111111111",
    "0111100010000100000",
    "0101011111111111111",
    "1101001000100000010",
    "1001101111000000011",
    "1111001010011111110",
    "0101111010110100011",
    "0101101110100000001",
    "1111011011111111111",
    "0001110110010001010"
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
        /*
        * NOTE: Co-ordinates are in format {Vertical, Horizontal}
        */
        {13, 0},     /* START */
        {12, 8}/* END */
    },

    .count = 2
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
        while(1) {
            stopMoving(); // Stop moving forevr once finished
        }
    }

    // Get next command.
    command = route.commands[commandIndex];
    if (commandIndex + 1 < route.length) {
        nextCommand = route.commands[commandIndex + 1];
    } else {
        nextCommand = CMD_FORWARD; // No next command; use normal one-cell movement.
    }
        

    // Execute it.
    // Execute the next command.
    switch (command)
    {
        case CMD_FORWARD:
            MoveForwardOneCell(nextCommand);
            break;

        case CMD_LEFT:
            TurnLeft();
            break;

        case CMD_RIGHT:
            TurnRight();
            break;

        case CMD_UTURN:
            UTurn();
            break;

        case CMD_LEFT_SHORT:
            LittleLeft();
            break;

        case CMD_RIGHT_SHORT:
            LittleRight();
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
            for (int i = 0; i < 10; i++) {
                Clock_PWM_SetDivider(24);
                LED_1_Write(1);
                LED_2_Write(1);
                LED_3_Write(1);
                CyDelay(200);
                Clock_PWM_SetDivider(12);
                LED_1_Write(0);
                LED_2_Write(0);
                LED_3_Write(0);
                CyDelay(200);
            }

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
    
    CyDelay(1000);


    // Route has now been calculated. Start robot movement.
    while (1)
    {
        ExecuteNextCommand();
    }


    return 0;
}