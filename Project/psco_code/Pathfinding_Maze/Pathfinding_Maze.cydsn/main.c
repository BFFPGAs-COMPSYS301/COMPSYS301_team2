
#include "project.h"
#include "astar.h"
#include "movements.c"

#define STARTDIRECTION DIR_RIGHT

const char *mazeInput[MAP_ROWS] =
{

    "0000000000000000000",
    "0101111111111111110",
    "0101010001000100010",
    "0101010101110111010",
    "0101011100010000010",
    "0111110111010111110",
    "0000000101010100010",
    "0111111101010101110",
    "0001010000010101000",
    "0111010111011101110",
    "0100010101010000010",
    "0111111101111101110",
    "0100000001000001000",
    "0111111101111111110",
    "0000000000000000000"
};


// NUMERICAL MAP This is automatically created from mazeInput.
uint8_t map[MAP_ROWS][MAP_COLS];

Checkpoints checkpoints =
{
    .points =
    {
        /*
        * NOTE: Co-ordinates are in format {Vertical, Horizontal}
        */
        {7, 1},
        {4, 5},
        {1, 1},
        {5, 9},
        {4, 7}
    },

    .count = 5
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
            //stopMoving(); // Stop moving forevr once finished
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


    // Route has now been calculated. Start robot movement.
    while (1)
    {
        ExecuteNextCommand();
        //PWM_1_WriteCompare(15);
        //PWM_2_WriteCompare(15);
        //goForwardSlow();
        CyDelay(100);
    }


    return 0;
}