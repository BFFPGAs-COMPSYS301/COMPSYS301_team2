#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define ROWS 15
#define COLS 19


typedef struct {
    int row;
    int col;
} Position;


/*
    Robot directions

    0 = UP
    1 = RIGHT
    2 = DOWN
    3 = LEFT
*/
typedef enum {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
} Direction;


/*
    Complete path
*/
typedef struct {
    Position *cells;
    int length;
} Path;


/*
    Manhattan distance
*/
int heuristic(Position a, Position b)
{
    return abs(a.row - b.row) +
           abs(a.col - b.col);
}


/*
    Run A*
*/
Path astar(
    int map[ROWS][COLS],
    Position start,
    Position target
)
{
    double gScore[ROWS][COLS];
    double fScore[ROWS][COLS];
    bool visited[ROWS][COLS];
    Position parent[ROWS][COLS];


    /*
        Initialise arrays
    */

    for (int r = 0; r < ROWS; r++) {

        for (int c = 0; c < COLS; c++) {

            gScore[r][c] = INFINITY;
            fScore[r][c] = INFINITY;
            visited[r][c] = false;

            parent[r][c] =
                (Position){-1, -1};
        }
    }


    /*
        Starting cell
    */

    gScore[start.row][start.col] = 0;

    fScore[start.row][start.col] =
        heuristic(start, target);


    /*
        Open set
    */

    Position openSet[ROWS * COLS];

    int openSize = 0;

    openSet[openSize++] = start;


    /*
        Directions

        UP
        RIGHT
        DOWN
        LEFT
    */

    int directions[4][2] = {

        {-1,  0},
        { 0,  1},
        { 1,  0},
        { 0, -1}
    };


    /*
        A*
    */

    while (openSize > 0) {

        /*
            Find lowest fScore
        */

        int bestIndex = 0;

        for (int i = 1; i < openSize; i++) {

            Position p =
                openSet[i];

            Position best =
                openSet[bestIndex];


            if (fScore[p.row][p.col] <
                fScore[best.row][best.col]) {

                bestIndex = i;
            }
        }


        Position current =
            openSet[bestIndex];


        /*
            Remove current from open set
        */

        openSet[bestIndex] =
            openSet[--openSize];


        /*
            Skip if already visited
        */

        if (visited[current.row][current.col])
            continue;


        visited[current.row][current.col] = true;


        /*
            Target reached
        */

        if (current.row == target.row &&
            current.col == target.col) {

            break;
        }


        /*
            Check neighbours
        */

        for (int i = 0; i < 4; i++) {

            int row =
                current.row +
                directions[i][0];

            int col =
                current.col +
                directions[i][1];


            /*
                Outside map
            */

            if (row < 0 || row >= ROWS ||
                col < 0 || col >= COLS)

                continue;


            /*
                Wall
            */

            if (map[row][col] == 1)
                continue;


            /*
                Already visited
            */

            if (visited[row][col])
                continue;


            /*
                New cost
            */

            double newGScore =
                gScore[current.row][current.col]
                + 1;


            /*
                Better path found
            */

            if (newGScore < gScore[row][col]) {

                gScore[row][col] =
                    newGScore;

                parent[row][col] =
                    current;

                fScore[row][col] =
                    newGScore +
                    heuristic(
                        (Position){row, col},
                        target
                    );


                openSet[openSize++] =
                    (Position){row, col};
            }
        }
    }


    /*
        Create path
    */

    Path path;

    path.cells = NULL;
    path.length = 0;


    /*
        No path
    */

    if (gScore[target.row][target.col] ==
        INFINITY) {

        return path;
    }


    /*
        Build path backwards
    */

    Position reversePath[ROWS * COLS];

    int pathLength = 0;

    Position current = target;


    while (1) {

        reversePath[pathLength++] =
            current;


        if (current.row == start.row &&
            current.col == start.col) {

            break;
        }


        current =
            parent[current.row][current.col];
    }


    /*
        Allocate final path
    */

    path.cells =
        malloc(pathLength *
               sizeof(Position));

    path.length =
        pathLength;


    /*
        Reverse path

        START -> TARGET
    */

    for (int i = 0; i < pathLength; i++) {

        path.cells[i] =
            reversePath[
                pathLength - 1 - i
            ];
    }


    return path;
}


/*
    Determine direction between two cells
*/
Direction getDirection(
    Position from,
    Position to
)
{
    if (to.row < from.row)
        return UP;

    if (to.col > from.col)
        return RIGHT;

    if (to.row > from.row)
        return DOWN;

    return LEFT;
}


/*
    Convert path into robot commands
*/
void printCommands(
    Path path,
    Direction startingDirection
)
{
    Direction facing =
        startingDirection;


    for (int i = 1;
         i < path.length;
         i++) {

        Direction required =
            getDirection(
                path.cells[i - 1],
                path.cells[i]
            );


        /*
            Calculate required turn

            0 = straight
            1 = right
            2 = U-turn
            3 = left
        */

        int turn =
            (required - facing + 4) % 4;


        if (turn == 1) {

            printf("RIGHT\n");
        }

        else if (turn == 2) {

            printf("RIGHT\n");
            printf("RIGHT\n");
        }

        else if (turn == 3) {

            printf("LEFT\n");
        }


        /*
            Turning does NOT move.

            FORWARD actually moves
            into the next cell.
        */

        printf("FORWARD\n");


        /*
            Robot is now facing
            the direction it moved.
        */

        facing = required;
    }
}


int main(void)
{
    /*
        =========================================
        PASTE YOUR MAP HERE
        =========================================
    */

    const char *mapInput[ROWS] = {

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


    /*
        Convert text map into
        integer map
    */

    int map[ROWS][COLS];


    for (int r = 0; r < ROWS; r++) {

        for (int c = 0; c < COLS; c++) {

            map[r][c] =
                mapInput[r][c] - '0';
        }
    }


    /*
        =========================================
        SET START AND TARGET HERE
        =========================================
    */

    Position start = {
        1,
        1
    };

    Position target = {
        13,
        17
    };


    /*
        =========================================
        SET INITIAL ROBOT DIRECTION HERE
        =========================================
    */

    Direction startingDirection = RIGHT;


    /*
        Run A* ONCE
    */

    Path path =
        astar(
            map,
            start,
            target
        );


    /*
        Check for path
    */

    if (path.length == 0) {

        printf("NO_PATH\n");
    }

    else {

        /*
            Generate complete
            movement sequence
        */

        printCommands(
            path,
            startingDirection
        );
    }


    /*
        Free path
    */

    free(path.cells);


    return 0;
}