/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "team.h"
#include "utility.h"

int getTeamOffset(Team team)
{
    switch (team)
    {
    case RED_TEAM:
    {
        return intRand(MAX_RED_TEAM_OFFSET, MIN_RED_TEAM_OFFSET);
    }
    case BLUE_TEAM:
    {
        return intRand(MAX_BLUE_TEAM_OFFSET, MIN_BLUE_TEAM_OFFSET);
    }
    default:
        printf("WARNING: invalid team type!\n");
        return 0;
        break;
    }
}