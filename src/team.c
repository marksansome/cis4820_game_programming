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
#include "tower.h"
#include "utility.h"
#include "valley.h"
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
    for (int i = 0; i < NUM_STARTING_TOWERS; i++)
    {
        int towerOffset = getTeamOffset(t->type);

        switch (t->type)
        {
        case RED_TEAM:
        {
            towerOffset = t->base->x2;
            towerOffset += TOWER_TO_BASE_OFFSET;
            break;
        }
        case BLUE_TEAM:
        {
            towerOffset = t->base->x1;
            towerOffset -= TOWER_TO_BASE_OFFSET;
            break;
        }
        default:
            printf("ERROR: Invalid team type\n");
            exit(1);
        }

        Tower *tow = createTower();
        initializeTower(tow, t->colour, towerOffset);

        addItem(t->towers, tow, TOWER);
        generateTower(tow);
    }
}

void updateTeam(Team *t, double currentTime, List *vehicleTargets, List *meteorCheck, List *meteorAdd)
{
    // move tower projectiles
    for (int i = 0; i < getListSize(t->towers); i++)
    {
        updateTowerProjectile(getItemAtIndex(t->towers, i)->ptr, vehicleTargets);
    }

    // move teams vehicles
    for (int i = 0; i < getListSize(t->vehicles); i++)
    {
        Vehicle *v = getItemAtIndex(t->vehicles, i)->ptr;
        if (currentTime - v->timeTracker >= v->speed)
        {
            v->timeTracker = currentTime;
            moveVehicle(v, t, meteorCheck);
            // vehicle health is updated with checking projectile collision
            if (v->health <= 0)
            {
                // remove destroyed vehicle
                Vehicle *rem = removeItemAtIndex(t->vehicles, i)->ptr;
                generateVehicle(rem, t->type, 1);

                // create explosion
                int explosionSize = 5;
                Valley *explosion = createValley();
                customInitializeValley(explosion, explosionSize, explosionSize, v->x1, v->y, v->z1 + 1);
                generateValley(explosion);
                free(explosion);

                // drop meteor if carrying one
                if (v->isCarryingMeteor)
                {
                    Meteor *m = rem->targetMeteor;
                    m->isCollected = 0;
                    m->isFalling = 1;
                    m->x = rem->x1;
                    m->y = rem->y;
                    m->z = rem->z1;
                    addItem(meteorAdd, m, METEOR);
                }

                // create the new vehicle
                Vehicle *new = createVehicle();
                initializeVehicle(new, rem->type, t);
                generateVehicle(new, t->type, 0);
                addItem(t->vehicles, new, VEHICLE);

                // free the old vehicle
                free(rem);
            }
        }
    }

    // draw teams meteor cube
    drawMeteorCube(t);
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

void drawMeteorCube(Team *t)
{
    int cubeCount = getListSize(t->meteors);
    int xOffset, yOffset, zOffset = 0;

    for (int i = 1; i <= cubeCount; i++)
    {
        xOffset = 0;
        yOffset = 0;
        zOffset = 0;

        if (i > 9 && i <= 18)
        {
            yOffset = 1;
        }
        else if (i > 18)
        {
            yOffset = 2;
        }
        else
        {
            yOffset = 0;
        }

        if ((i % 9) > 3 && (i % 9) <= 6)
        {
            xOffset = 1;
        }
        else if ((i % 9) > 6 && (i % 9) <= 8)
        {
            xOffset = 2;
        }
        else if (i % 9 == 0)
        {
            xOffset = 2;
        }
        else
        {
            xOffset = 0;
        }

        zOffset = i % 3;

        switch (t->type)
        {
        case RED_TEAM:
        {
            world[t->base->x1 - xOffset - 2][t->base->y1 + yOffset][t->base->z1 - 1 - zOffset] = getColour(DARK_GRAY);
            break;
        }
        case BLUE_TEAM:
        {
            world[t->base->x2 + 1 + xOffset][t->base->y1 + yOffset][t->base->z1 - 3 + zOffset] = getColour(DARK_GRAY);
            break;
        }
        default:
            printf("WARNING: Invalid team type\n");
            break;
        }
    }
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
