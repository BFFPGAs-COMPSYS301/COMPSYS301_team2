
#include "project.h"
#include "astar.h"


// Manhatten Distance
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


// GET DIRECTION BETWEEN TWO ADJACENT CELLS
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


// ADD COMMAND TO ROUTE
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


// ADD TURN TO ROUTE
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

    // Already facing the correct direction.
    if (turn == 0)
    {
        return true;
    }

    // Right turn.
    if (turn == 1)
    {
        if (!AddCommand(route, CMD_RIGHT))
        {
            return false;
        }
    }

    // U-turn: add one dedicated command.
    else if (turn == 2)
    {
        if (!AddCommand(route, CMD_UTURN))
        {
            return false;
        }
    }

    // Left turn.
    else
    {
        if (!AddCommand(route, CMD_LEFT))
        {
            return false;
        }
    }

    // Update the direction after the turn
    *currentDirection = requiredDirection;

    return true;
}

// Identify short turns
static void MarkShortTurnSequences(
    Route *route,
    uint16_t segmentStart
)
{
    uint16_t i;

    for (i = segmentStart;
         i + 2 < route->length;
         i++)
    {
        Command first = route->commands[i];
        Command middle = route->commands[i + 1];
        Command last = route->commands[i + 2];

        if (middle != CMD_FORWARD)
            continue;

        if ((first == CMD_LEFT || first == CMD_RIGHT || first == CMD_LEFT_SHORT || first == CMD_RIGHT_SHORT) &&
            (last == CMD_LEFT || last == CMD_RIGHT || last == CMD_LEFT_SHORT || last == CMD_RIGHT_SHORT || last == CMD_UTURN))
        {
            route->commands[i] =
                (first == CMD_LEFT || first == CMD_LEFT_SHORT)
                ? CMD_LEFT_SHORT
                : CMD_RIGHT_SHORT;

       
        if (last != CMD_UTURN)
    {
        route->commands[i + 2] =
            (last == CMD_RIGHT || last == CMD_RIGHT_SHORT)
            ? CMD_RIGHT_SHORT
            : CMD_LEFT_SHORT;
    }
        }
    }
}

static void ShortBeforeUturn(
    Route *route,
    uint16_t segmentStart
)
{
    uint16_t i;

    for (i = segmentStart;
         i + 3 < route->length;
         i++)
    {
        Command first = route->commands[i];
        Command middle1 = route->commands[i + 1];
        Command middle2 = route->commands[i + 2];
        Command last = route->commands[i + 3];


        if (middle1 != CMD_FORWARD || middle2 != CMD_FORWARD)
            continue;

        if ((first == CMD_LEFT || first == CMD_RIGHT || first == CMD_LEFT_SHORT || first == CMD_RIGHT_SHORT) &&
            (last == CMD_UTURN))
        {
            route->commands[i] =
                (first == CMD_LEFT || first == CMD_LEFT_SHORT)
                ? CMD_LEFT_SHORT
                : CMD_RIGHT_SHORT;
        }
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

    uint16_t steps[MAP_ROWS][MAP_COLS][4];
    uint16_t turns[MAP_ROWS][MAP_COLS][4];
    bool visited[MAP_ROWS][MAP_COLS][4];

    int16_t parentRow[MAP_ROWS][MAP_COLS][4];
    int16_t parentCol[MAP_ROWS][MAP_COLS][4];
    int8_t parentDir[MAP_ROWS][MAP_COLS][4];

    static const int8_t directions[4][2] =
    {
        {-1,  0},  /* UP */
        { 0,  1},  /* RIGHT */
        { 1,  0},  /* DOWN */
        { 0, -1}   /* LEFT */
    };

    // Initialise every search state.
    for (uint8_t r = 0; r < MAP_ROWS; r++)
    {
        for (uint8_t c = 0; c < MAP_COLS; c++)
        {
            for (uint8_t d = 0; d < 4; d++)
            {
                steps[r][c][d] = 65535;
                turns[r][c][d] = 65535;
                visited[r][c][d] = false;

                parentRow[r][c][d] = -1;
                parentCol[r][c][d] = -1;
                parentDir[r][c][d] = -1;
            }
        }
    }

    /* Initial state: start cell, original robot direction. */
    steps[start.row][start.col][startingDirection] = 0;
    turns[start.row][start.col][startingDirection] = 0;

    int16_t endRow = -1;
    int16_t endCol = -1;
    int8_t endDir = -1;

    // Dijkstra search with costs: compare steps first, then turns.
    while (true)
    {
        int16_t bestRow = -1;
        int16_t bestCol = -1;
        int8_t bestDir = -1;

        for (uint8_t r = 0; r < MAP_ROWS; r++)
        {
            for (uint8_t c = 0; c < MAP_COLS; c++)
            {
                for (uint8_t d = 0; d < 4; d++)
                {
                    if (visited[r][c][d] ||
                        steps[r][c][d] == 65535)
                    {
                        continue;
                    }

                    if (bestRow == -1 ||
                        steps[r][c][d] <
                            steps[bestRow][bestCol][bestDir] ||
                        (steps[r][c][d] ==
                            steps[bestRow][bestCol][bestDir] &&
                         turns[r][c][d] <
                            turns[bestRow][bestCol][bestDir]))
                    {
                        bestRow = r;
                        bestCol = c;
                        bestDir = d;
                    }
                }
            }
        }

        // No reachable states remain.
        if (bestRow == -1)
            return false;

        visited[bestRow][bestCol][bestDir] = true;

        /* The first target state selected is optimal. */
        if (bestRow == target.row &&
            bestCol == target.col)
        {
            endRow = bestRow;
            endCol = bestCol;
            endDir = bestDir;
            break;
        }

        /* Explore all four possible next directions. */
        for (uint8_t d = 0; d < 4; d++)
        {
            int16_t nr = bestRow + directions[d][0];
            int16_t nc = bestCol + directions[d][1];

            if (nr < 0 || nr >= MAP_ROWS ||
                nc < 0 || nc >= MAP_COLS)
            {
                continue;
            }

            /* 1 = Path, 0 = Wall. */
            if (map[nr][nc] != 1)
                continue;

            if (visited[nr][nc][d])
                continue;

            uint16_t newSteps =
                steps[bestRow][bestCol][bestDir] + 1;

            uint16_t newTurns =
                turns[bestRow][bestCol][bestDir];

            // Changing direction adds one turn.
            if (d != bestDir)
                newTurns++;

            // Prefer fewer steps. If steps tie, prefer fewer turns.
            if (newSteps < steps[nr][nc][d] ||
                (newSteps == steps[nr][nc][d] &&
                 newTurns < turns[nr][nc][d]))
            {
                steps[nr][nc][d] = newSteps;
                turns[nr][nc][d] = newTurns;

                parentRow[nr][nc][d] = bestRow;
                parentCol[nr][nc][d] = bestCol;
                parentDir[nr][nc][d] = bestDir;
            }
        }
    }

    if (endRow == -1)
        return false;

    // Reconstruct the path backwards from the target.
    Position reversePath[MAX_CELLS];
    uint16_t pathLength = 0;

    int16_t r = endRow;
    int16_t c = endCol;
    int8_t d = endDir;

    while (true)
    {
        if (pathLength >= MAX_CELLS)
            return false;

        reversePath[pathLength].row = (uint8_t)r;
        reversePath[pathLength].col = (uint8_t)c;
        pathLength++;

        // Reached the original search state.
        if (r == start.row &&
            c == start.col &&
            d == startingDirection)
        {
            break;
        }

        int16_t pr = parentRow[r][c][d];
        int16_t pc = parentCol[r][c][d];
        int8_t pd = parentDir[r][c][d];

        if (pr < 0 || pc < 0 || pd < 0)
            return false;

        r = pr;
        c = pc;
        d = pd;
    }

    // Convert the reconstructed path into robot commands, moving from START towards TARGET.
    Direction direction = startingDirection;

    for (int16_t i = (int16_t)pathLength - 1; i > 0; i--)
    {
        Position from = reversePath[i];
        Position to = reversePath[i - 1];

        Direction requiredDirection = GetDirection(from, to);

        if (!AddTurn(route, &direction, requiredDirection))
            return false;

        if (!AddCommand(route, CMD_FORWARD))
            return false;
    }

    *finalDirection = direction;
    
    return true;
}

// Build complete route, running A* once for every pair of checkpoints.
bool AStar_BuildRoute(
    const uint8_t map[MAP_ROWS][MAP_COLS],
    const Checkpoints *checkpoints,
    Direction startingDirection,
    Route *route
)
{
    Direction currentDirection = startingDirection;

    // Validate pointers before dereferencing them.
    if (map == NULL ||
        checkpoints == NULL ||
        route == NULL)
    {
        return false;
    }

    // We need at least a start and destination.
    if (checkpoints->count < 2 ||
        checkpoints->count > MAX_CHECKPOINTS)
    {
        return false;
    }

    // Validate every checkpoint before searching.
    for (uint8_t i = 0; i < checkpoints->count; i++)
    {
        Position p = checkpoints->points[i];

        if (p.row >= MAP_ROWS ||
            p.col >= MAP_COLS)
        {
            return false;
        }

        // 1 = open; 0 = wall.
        if (map[p.row][p.col] != 1)
        {
            return false;
        }
    }

    // Initialize the complete route.
    route->length = 0;
    route->checkpointCount = checkpoints->count;
    route->finalDirection = startingDirection;
    route->checkpointCommand[0] = 0;



    // Calculate every section.
    for (uint8_t i = 0;
         i < checkpoints->count - 1;
         i++)
    {
        Direction newDirection;


        // Calculate:  Point i -> Point i+1

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


        // Robot's direction when it arrives at this checkpoint.
        currentDirection =
            newDirection;


        // Store the command index at which this checkpoint is reached.
        route->checkpointCommand[i + 1] =
            route->length;
    }
    
    MarkShortTurnSequences(route, 0);
    ShortBeforeUturn(route, 0);

    // Store final direction.
    route->finalDirection =
        currentDirection;
    
    return true;
}