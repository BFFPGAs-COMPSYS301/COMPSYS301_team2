#include "project.h"
#include "astar.h"
#include "movement.h"

/*
    Each encoder count is ~0.9mm
    Each cell is ~18.5cm
    
    one cell = 205 ecoder counts
*/

uint8_t distanceTravelled;
uint8_t cellLength = 205;

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

uint8_t map[MAP_ROWS][MAP_COLS];


/* =========================================================
 * CHECKPOINTS
 *
 * Top-left cell = {0,0}
 *
 * The order here is the order the robot will visit.
 * ========================================================= */

Checkpoints checkpoints =
{
    .points =
    {
        {1, 1},     /* START */
        /*
        {3, 3},     // CHECKPOINT 1
        {5, 7},     // CHECKPOINT 2
        {7, 15},    // CHECKPOINT 3
        */
        {13, 17}    /* END */
    },

    .count = 2
};


/* =========================================================
 * COMPLETE ROUTE
 * ========================================================= */

Route route;


/* =========================================================
 * ROBOT STATE
 * ========================================================= */

uint16_t commandIndex = 0;


/*
 * The next checkpoint the robot needs to reach.
 *
 * Checkpoint 0 is the starting position,
 * so we begin waiting for checkpoint 1.
 */

uint8_t nextCheckpoint = 1;


/* =========================================================
 * CONVERT PASTED MAP TO NUMERICAL MAP
 * ========================================================= */

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


/* =========================================================
 * BUILD THE COMPLETE ROUTE
 *
 * Call this once before the robot starts moving.
 * ========================================================= */

bool BuildRoute(void)
{
    LoadMap();


    return AStar_BuildRoute(
        map,
        &checkpoints,
        DIR_RIGHT,
        &route
    );
}


/* =========================================================
 * EXECUTE NEXT COMMAND
 *
 * Replace the motor functions below with your
 * actual PSoC motor-control functions.
 * ========================================================= */

void ExecuteNextCommand(void)
{
    Command command;

    // Check If we have reached the end
    if (commandIndex >= route.length)
    {
        //Robot has reached the final point. Add whatever you want to happen here.
        return;
    }

    // Get next command.

    command = route.commands[commandIndex];

    // Execute it.
    switch (command)
    {
        case CMD_FORWARD:
            stopMoving();
            QuadDec_1_SetCounter(0);
            distanceTravelled = 0;
            // Move forward exactly one cell.
            while(distanceTravelled < cellLength) {
                if (LED1_Read() == 1) {
                    MoveForwardOneCell();
                } else {
                    oneSensorCorrect();
                }
                distanceTravelled = QuadDec_1_GetCounter();
            }
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


/* =========================================================
 * EXAMPLE PROGRAM START
 * ========================================================= */

int main(void)
{
    CyGlobalIntEnable;

    PWM_1_Start();
    PWM_2_Start();

    // Stop motors before doing anything else.
    PWM_1_WriteCompare(45);
    PWM_2_WriteCompare(45);

    if (!BuildRoute())
    {
        while (1)
        {
            PWM_1_WriteCompare(45);
            PWM_2_WriteCompare(45);
        }
    }

    while (1)
    {
        ExecuteNextCommand();
    }
    return 0;
}