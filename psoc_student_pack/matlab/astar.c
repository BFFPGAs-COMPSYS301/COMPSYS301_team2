#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    Position *data;
    int size;
    int capacity;
} PositionList;

/* ---------------------------------------------------------
   Dynamic list functions
   --------------------------------------------------------- */

void initList(PositionList *list, int capacity)
{
    list->data = malloc(capacity * sizeof(Position));
    list->size = 0;
    list->capacity = capacity;
}

void addPosition(PositionList *list, Position position)
{
    if (list->size >= list->capacity) {
        list->capacity *= 2;

        list->data = realloc(
            list->data,
            list->capacity * sizeof(Position)
        );
    }

    list->data[list->size++] = position;
}

void removePosition(PositionList *list, int index)
{
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
}

void freeList(PositionList *list)
{
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

/* ---------------------------------------------------------
   A* algorithm
   --------------------------------------------------------- */

void astar(
    int **map,
    int maprows,
    int mapcols,
    Position start,
    Position target,
    PositionList *retvisited,
    PositionList *retsteps
)
{
    /*
        gScore = cost from start to each cell
        fScore = estimated total cost from start to target
    */

    double **gScore = malloc(maprows * sizeof(double *));
    double **fScore = malloc(maprows * sizeof(double *));

    bool **visited = malloc(maprows * sizeof(bool *));

    Position **parent = malloc(maprows * sizeof(Position *));

    for (int r = 0; r < maprows; r++) {
        gScore[r] = malloc(mapcols * sizeof(double));
        fScore[r] = malloc(mapcols * sizeof(double));
        visited[r] = malloc(mapcols * sizeof(bool));
        parent[r] = malloc(mapcols * sizeof(Position));

        for (int c = 0; c < mapcols; c++) {
            gScore[r][c] = INFINITY;
            fScore[r][c] = INFINITY;
            visited[r][c] = false;

            parent[r][c].row = -1;
            parent[r][c].col = -1;
        }
    }

    /*
        Distance from start to itself is zero
    */
    gScore[start.row][start.col] = 0;

    /*
        Manhattan distance heuristic
    */
    fScore[start.row][start.col] =
        abs(start.row - target.row) +
        abs(start.col - target.col);

    /*
        Open set
    */
    PositionList openSet;
    initList(&openSet, 16);

    addPosition(&openSet, start);

    /*
        Directions:
            up
            down
            left
            right
    */
    int directions[4][2] = {
        {-1,  0},
        { 1,  0},
        { 0, -1},
        { 0,  1}
    };

    /*
        A* algorithm
    */
    while (openSet.size > 0) {

        /*
            Find the cell in openSet with the
            smallest fScore
        */
        int bestIndex = 0;
        double bestScore = INFINITY;

        for (int i = 0; i < openSet.size; i++) {

            int row = openSet.data[i].row;
            int col = openSet.data[i].col;

            if (fScore[row][col] < bestScore) {
                bestScore = fScore[row][col];
                bestIndex = i;
            }
        }

        /*
            Get cell with smallest fScore
        */
        Position current = openSet.data[bestIndex];

        /*
            Remove current from openSet
        */
        removePosition(&openSet, bestIndex);

        /*
            If already visited, skip it
        */
        if (visited[current.row][current.col]) {
            continue;
        }

        /*
            Mark current as visited
        */
        visited[current.row][current.col] = true;

        /*
            Record visited cell
        */
        addPosition(retvisited, current);

        /*
            Have we reached the target?
        */
        if (current.row == target.row &&
            current.col == target.col) {

            break;
        }

        /*
            Check each neighbouring cell
        */
        for (int k = 0; k < 4; k++) {

            int row = current.row + directions[k][0];
            int col = current.col + directions[k][1];

            /*
                Check that neighbour is inside map
            */
            if (row >= 0 && row < maprows &&
                col >= 0 && col < mapcols) {

                /*
                    Check that neighbour is not a wall

                    MATLAB:
                        map(row,col) == 0

                    C uses zero-based indexing.
                */
                if (map[row][col] == 0) {

                    /*
                        Ignore already visited cells
                    */
                    if (!visited[row][col]) {

                        /*
                            Cost of moving to neighbour
                        */
                        double movementCost = 1.0;

                        /*
                            Calculate new gScore
                        */
                        double newGScore =
                            gScore[current.row][current.col]
                            + movementCost;

                        /*
                            If this is a better route
                        */
                        if (newGScore < gScore[row][col]) {

                            /*
                                Store new cost
                            */
                            gScore[row][col] = newGScore;

                            /*
                                Store parent
                            */
                            parent[row][col] = current;

                            /*
                                Manhattan heuristic
                            */
                            int heuristic =
                                abs(row - target.row) +
                                abs(col - target.col);

                            /*
                                Calculate fScore
                            */
                            fScore[row][col] =
                                newGScore + heuristic;

                            /*
                                Add neighbour to openSet
                            */
                            Position neighbour = {
                                row,
                                col
                            };

                            addPosition(&openSet, neighbour);
                        }
                    }
                }
            }
        }
    }

    /*
        Reconstruct path
    */

    /*
        Check whether target was reached
    */
    if (gScore[target.row][target.col] != INFINITY) {

        Position current = target;

        /*
            Build path backwards.

            We temporarily store the path backwards,
            then reverse it.
        */
        PositionList reversePath;
        initList(&reversePath, 16);

        while (!(current.row == start.row &&
                 current.col == start.col)) {

            addPosition(&reversePath, current);

            current = parent[current.row][current.col];
        }

        /*
            Add starting location
        */
        addPosition(&reversePath, start);

        /*
            Reverse path to get start -> target
        */
        for (int i = reversePath.size - 1; i >= 0; i--) {
            addPosition(
                retsteps,
                reversePath.data[i]
            );
        }

        freeList(&reversePath);
    }

    /*
        Free memory
    */
    freeList(&openSet);

    for (int r = 0; r < maprows; r++) {
        free(gScore[r]);
        free(fScore[r]);
        free(visited[r]);
        free(parent[r]);
    }

    free(gScore);
    free(fScore);
    free(visited);
    free(parent);
}

/* ---------------------------------------------------------
   Example
   --------------------------------------------------------- */

void printMap(
    int **map,
    int rows,
    int cols,
    PositionList *path
)
{
    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            char character = map[r][c] ? '#' : '.';

            /*
                Check whether this cell is part of path
            */
            for (int i = 0; i < path->size; i++) {

                if (path->data[i].row == r &&
                    path->data[i].col == c) {

                    character = '*';
                    break;
                }
            }

            printf("%c ", character);
        }

        printf("\n");
    }
}

int main(void)
{
    /*
        Example map

        0 = open
        1 = wall
    */

    int rows = 10;
    int cols = 10;

    int mapData[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,0,0,0,1,1,0},
        {0,0,0,1,0,1,0,0,0,0},
        {0,1,0,0,0,1,1,1,0,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,1,1,1,0,1,1,0},
        {0,1,0,0,0,0,0,1,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    /*
        Convert the 2D array into an array of pointers
        so astar() can use map[row][col].
    */

    int **map = malloc(rows * sizeof(int *));

    for (int r = 0; r < rows; r++) {
        map[r] = mapData[r];
    }

    /*
        MATLAB uses 1-based coordinates.

        C uses 0-based coordinates.

        MATLAB:
            startlocation = [1 1]

        C:
            start = {0, 0}
    */

    Position start = {0, 0};
    Position target = {9, 9};

    PositionList visited;
    PositionList steps;

    initList(&visited, 32);
    initList(&steps, 32);

    /*
        Run A*
    */
    astar(
        map,
        rows,
        cols,
        start,
        target,
        &visited,
        &steps
    );

    /*
        Print visited cells
    */
    printf("Visited cells:\n");

    for (int i = 0; i < visited.size; i++) {
        printf(
            "(%d, %d)\n",
            visited.data[i].row,
            visited.data[i].col
        );
    }

    /*
        Print path
    */
    printf("\nPath:\n");

    for (int i = 0; i < steps.size; i++) {
        printf(
            "(%d, %d)\n",
            steps.data[i].row,
            steps.data[i].col
        );
    }

    /*
        Print map
    */
    printf("\nMap:\n");

    printMap(
        map,
        rows,
        cols,
        &steps
    );

    freeList(&visited);
    freeList(&steps);
    free(map);

    return 0;
}