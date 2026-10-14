
#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdint.h>
#include <stdbool.h>
#include "astar.h"

typedef enum {
    NAV_IDLE,
    NAV_FOLLOW_LINE,
    NAV_APPROACH_TURN,
    NAV_CORNER_SEARCH,
    NAV_TURN_LEFT,
    NAV_TURN_RIGHT,
    NAV_REACQUIRE_LINE,
    NAV_FINISHED,
    NAV_ERROR
} NavigationState;

typedef struct {
    NavigationState state;

    const Route *route;
    uint16_t commandIndex;

    Position expectedCell;
    Direction expectedHeading;

    float distanceOnStraightMm;
    float expectedTurnDistanceMm;

    bool landmarkConfirmed;
} Navigator;

#endif
