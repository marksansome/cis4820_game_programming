/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "graphics.h"
#include "team.h"
#include "utility.h"
#include "vehicle.h"

Team *createTeam()
{
    Team *t = (Team *)malloc(sizeof(Team));
    if (t == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    t->type = INVALID_TEAM;
    t->base = NULL;
    t->vehicles = NULL;
    t->towers = NULL;
    t->meteors = NULL;
    t->colour = 0;

    return t;
}

void initializeTeam(Team *t, team_type type)
{
    // initialize values
    t->type = type;
    t->vehicles = createList();
    t->towers = createList();
    t->meteors = createList();

    // set values based on team_type
    switch (type)
    {
    case RED_TEAM:
    {
        t->colour = getColour(RED_TEAM_COLOUR);
        break;
    }
    case BLUE_TEAM:
    {
        t->colour = getColour(BLUE_TEAM_COLOUR);
        break;
    }
    default:
        printf("ERROR: invalid team type!\n");
        exit(1);
    }
}

void initializeTeamStartingObjects(Team *t)
{
    // create starting data
    // vehicles, trucks
    for (int i = 0; i < NUM_STARTING_TRUCKS; i++)
    {
        Vehicle *v = createVehicle();
        initializeVehicle(v, TRUCK_VEHICLE, t);

        addItem(t->vehicles, v, VEHICLE);
        generateVehicle(v, t->type, 0);
    }

    // towers
}

int checkTeamCollision(Team *t, int y, int x1, int z1, int x2, int z2)
{
    for (int x = x1; x < x2; x++)
    {
        for (int z = z1; z < z2; z++)
        {
            if (y > 0)
            {
                if (world[x][y - 1][z] == t->colour)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int getTeamOffset(team_type type)
{
    switch (type)
    {
    case RED_TEAM:
    {
        return intRand(MAX_RED_TEAM_X_OFFSET, MIN_RED_TEAM_X_OFFSET);
    }
    case BLUE_TEAM:
    {
        return intRand(MAX_BLUE_TEAM_X_OFFSET, MIN_BLUE_TEAM_X_OFFSET);
    }
    default:
        printf("WARNING: invalid team type!\n");
        return 0;
        break;
    }
}
