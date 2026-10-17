
#include "project.h"
#include "astar.h"


/* =========================================================
 * MANHATTAN DISTANCE
 * ========================================================= */

static uint16_t Heuristic(
    Position a,
    Position b
)
{
    uint16_t rowDistance;
    uint16_t colDistance;


    if (a.row > b.row)
        rowDistance = a.row - b.row;
    else
        rowDistance = b.row - a.row;


    if (a.col > b.col)
        colDistance = a.col - b.col;
    else
        colDistance = b.col - a.col;


    return rowDistance + colDistance;
}


/* =========================================================
 * GET DIRECTION BETWEEN TWO ADJACENT CELLS
 * ========================================================= */

static Direction GetDirection(
    Position from,
    Position to
)
{
    if (to.row < from.row)
        return DIR_UP;

    if (to.col > from.col)
        return DIR_RIGHT;

    if (to.row > from.row)
        return DIR_DOWN;

    return DIR_LEFT;
}


/* =========================================================
 * ADD COMMAND TO ROUTE
 * ========================================================= */

static bool AddCommand(
    Route *route,
    Command command
)
{
    if (route->length >= MAX_COMMANDS)
        return false;


    route->commands[route->length] =
        command;

    route->length++;

    return true;
}


/* =========================================================
 * ADD TURN TO ROUTE
 *
 * Turning does NOT move the robot.
 * ========================================================= */

static bool AddTurn(
    Route *route,
    Direction *currentDirection,
    Direction requiredDirection
)
{
    int turn;

    /*
     * Calculate clockwise difference.
     *
     * 0 = straight
     * 1 = right
     * 2 = U-turn
     * 3 = left
     */

    turn =
        ((int)requiredDirection -
         (int)(*currentDirection) +
         4) % 4;

    /*
     * Already facing the correct direction.
     */

    if (turn == 0)
    {
        return true;
    }

    /*
     * Right turn.
     */

    if (turn == 1)
    {
        if (!AddCommand(route, CMD_RIGHT))
        {
            return false;
        }
    }

    /*
     * U-turn: add one dedicated command.
     */

    else if (turn == 2)
    {
        if (!AddCommand(route, CMD_UTURN))
        {
            return false;
        }
    }

    /*
     * Left turn.
     */

    else
    {
        if (!AddCommand(route, CMD_LEFT))
        {
            return false;
        }
    }

    /*
     * Update the direction after the turn.
     * The physical movement is performed later.
     */

    *currentDirection = requiredDirection;

    return true;
}

/* =========================================================
 * IDENTIFY TURNS WITH A ONE-CELL STRAIGHT SECTION BETWEEN
 * THEM.
 *
 * LEFT, FORWARD, RIGHT
 *     -> LEFT_SHORT, FORWARD, RIGHT_SHORT
 *
 * RIGHT, FORWARD, LEFT
 *     -> RIGHT_SHORT, FORWARD, LEFT_SHORT
 *
 * No commands are removed or reordered.
 * ========================================================= */

static void MarkShortTurnSequences(
    Route *route,
    uint16_t segmentStart
)
{
    uint16_t i = segmentStart;

    while (i + 2 < route->length)
    {
        Command first = route->commands[i];
        Command middle = route->commands[i + 1];
        Command last = route->commands[i + 2];

        if (middle == CMD_FORWARD &&
            first == CMD_LEFT &&
            last == CMD_RIGHT)
        {
            route->commands[i] = CMD_LEFT_SHORT;
            route->commands[i + 2] = CMD_RIGHT_SHORT;

            i += 3;
            continue;
        }

        if (middle == CMD_FORWARD &&
            first == CMD_RIGHT &&
            last == CMD_LEFT)
        {
            route->commands[i] = CMD_RIGHT_SHORT;
            route->commands[i + 2] = CMD_LEFT_SHORT;

            i += 3;
            continue;
        }

        i++;
    }
}

static bool AStarSegment(
    const uint8_t map[MAP_ROWS][MAP_COLS],
    Position start,
    Position target,
    Direction startingDirection,
    Route *route,
    Direction *finalDirection
)
{
    uint16_t segmentStart = route->length;
    uint16_t gScore[MAP_ROWS][MAP_COLS];
    uint16_t fScore[MAP_ROWS][MAP_COLS];

    bool visited[MAP_ROWS][MAP_COLS];

    Position parent[MAP_ROWS][MAP_COLS];

    Position openSet[MAX_CELLS];

    uint16_t openSize = 0;


    /*
     * Initialise arrays.
     */

    for (uint8_t row = 0;
         row < MAP_ROWS;
         row++)
    {
        for (uint8_t col = 0;
             col < MAP_COLS;
             col++)
        {
            gScore[row][col] = 65535;
            fScore[row][col] = 65535;

            visited[row][col] = false;

            parent[row][col].row = 255;
            parent[row][col].col = 255;
        }
    }


    /*
     * Starting position.
     */

    gScore[start.row][start.col] = 0;

    fScore[start.row][start.col] =
        Heuristic(start, target);


    openSet[openSize++] = start;


    /*
     * Directions:
     *
     * 0 = UP
     * 1 = RIGHT
     * 2 = DOWN
     * 3 = LEFT
     */

    static const int8_t directions[4][2] =
    {
        {-1,  0},
        { 0,  1},
        { 1,  0},
        { 0, -1}
    };


    /* =====================================================
     * A* SEARCH
     * ===================================================== */

    while (openSize > 0)
    {
        uint16_t bestIndex = 0;


        /*
         * Find the cell with the lowest fScore.
         */

        for (uint16_t i = 1;
             i < openSize;
             i++)
        {
            Position a = openSet[i];
            Position b = openSet[bestIndex];


            if (fScore[a.row][a.col] <
                fScore[b.row][b.col])
            {
                bestIndex = i;
            }
        }


        /*
         * Get current cell.
         */

        Position current =
            openSet[bestIndex];


        /*
         * Remove current cell from open set.
         */

        openSet[bestIndex] =
            openSet[openSize - 1];

        openSize--;


        /*
         * Ignore if already processed.
         */

        if (visited[current.row][current.col])
            continue;


        visited[current.row][current.col] = true;


        /*
         * Have we reached the target?
         */

        if (current.row == target.row &&
            current.col == target.col)
        {
            break;
        }


        /*
         * Check all four neighbouring cells.
         */

        for (uint8_t d = 0;
             d < 4;
             d++)
        {
            int16_t newRow =
                current.row +
                directions[d][0];

            int16_t newCol =
                current.col +
                directions[d][1];


            /*
             * Check map boundaries.
             */

            if (newRow < 0 ||
                newRow >= MAP_ROWS ||
                newCol < 0 ||
                newCol >= MAP_COLS)
            {
                continue;
            }


            /*
             * Check for wall.
             *
             * 1 = wall
             * 0 = open
             */

            if (map[newRow][newCol] != 1)
                continue;


            /*
             * Already processed.
             */

            if (visited[newRow][newCol])
                continue;


            /*
             * Every cell movement costs 1.
             */

            uint16_t newGScore =
                gScore[current.row][current.col] + 1;


            /*
             * Is this a better path?
             */

            if (newGScore <
                gScore[newRow][newCol])
            {
                Position neighbour;


                neighbour.row = newRow;
                neighbour.col = newCol;


                gScore[newRow][newCol] =
                    newGScore;


                parent[newRow][newCol] =
                    current;


                fScore[newRow][newCol] =
                    newGScore +
                    Heuristic(
                        neighbour,
                        target
                    );


                /*
                 * Add neighbour to open set.
                 */

                if (openSize >= MAX_CELLS)
                    return false;


                openSet[openSize++] =
                    neighbour;
            }
        }
    }


    /*
     * If target was never visited,
     * there is no route.
     */

    if (!visited[target.row][target.col])
        return false;


    /* =====================================================
     * RECONSTRUCT PATH
     *
     * Initially creates:
     *
     *     TARGET
     *     CELL
     *     CELL
     *     START
     * ===================================================== */

    Position reversePath[MAX_CELLS];

    uint16_t pathLength = 0;

    Position current = target;


    while (1)
    {
        if (pathLength >= MAX_CELLS)
            return false;


        reversePath[pathLength++] =
            current;


        /*
         * Reached start.
         */

        if (current.row == start.row &&
            current.col == start.col)
        {
            break;
        }


        current =
            parent[current.row][current.col];


        /*
         * Invalid parent.
         */

        if (current.row == 255)
            return false;
    }


    /* =====================================================
     * CONVERT PATH TO ROBOT COMMANDS
     * ===================================================== */

    Direction direction =
        startingDirection;


    /*
     * Walk backwards through reversePath
     * so that we process:
     *
     *     START -> TARGET
     */

    for (int16_t i = pathLength - 1;
         i > 0;
         i--)
    {
        Position from =
            reversePath[i];

        Position to =
            reversePath[i - 1];


        /*
         * Direction required to move
         * from this cell to the next.
         */

        Direction requiredDirection =
            GetDirection(
                from,
                to
            );


        /*
         * Turn if necessary.
         *
         * Turning does NOT move.
         */

        if (!AddTurn(
                route,
                &direction,
                requiredDirection))
        {
            return false;
        }


        /*
         * Move forward one cell.
         */

        if (!AddCommand(
                route,
                CMD_FORWARD))
        {
            return false;
        }
    }


    /*
     * Return the final direction.
     */

    MarkShortTurnSequences(route, segmentStart);
    *finalDirection = direction;
    
    return true;
}


/* =========================================================
 * BUILD COMPLETE ROUTE
 *
 * Runs A* once for every pair of checkpoints.
 *
 * Example:
 *
 *     Point 0 -> Point 1
 *     Point 1 -> Point 2
 *     Point 2 -> Point 3
 *     Point 3 -> Point 4
 *
 * The resulting commands are combined into
 * one complete command array.
 * ========================================================= */

bool AStar_BuildRoute(
    const uint8_t map[MAP_ROWS][MAP_COLS],
    const Checkpoints *checkpoints,
    Direction startingDirection,
    Route *route
)
{
    Direction currentDirection =
        startingDirection;


    /*
     * Need at least two points:
     *
     * START -> END
     */

    if (checkpoints->count < 2)
        return false;


    /*
     * Make sure checkpoint count is valid.
     */

    if (checkpoints->count >
        MAX_CHECKPOINTS)
    {
        return false;
    }


    /*
     * Initialise route.
     */

    route->length = 0;

    route->checkpointCount =
        checkpoints->count;

    route->finalDirection =
        startingDirection;


    /*
     * Starting point is checkpoint 0.
     *
     * No commands have been executed yet.
     */

    route->checkpointCommand[0] = 0;


    /*
     * Calculate every section.
     */

    for (uint8_t i = 0;
         i < checkpoints->count - 1;
         i++)
    {
        Direction newDirection;


        /*
         * Calculate:

         *     Point i -> Point i+1
         */

        if (!AStarSegment(
                map,
                checkpoints->points[i],
                checkpoints->points[i + 1],
                currentDirection,
                route,
                &newDirection))
        {
            return false;
        }


        /*
         * Robot's direction when it arrives
         * at this checkpoint.
         */

        currentDirection =
            newDirection;


        /*
         * Store the command index at which
         * this checkpoint is reached.
         */

        route->checkpointCommand[i + 1] =
            route->length;
    }


    /*
     * Store final direction.
     */

    route->finalDirection =
        currentDirection;


    return true;
}