/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "team.h"
#include "utility.h"
#include "vehicle.h"

Vehicle *createVehicle()
{
    Vehicle *v = (Vehicle *)malloc(sizeof(Vehicle));
    if (v == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    v->colour = 0;
    v->state = INVALID_VEHICLE_STATE;
    v->y = 0;
    v->x1 = 0;
    v->z1 = 0;
    v->x2 = 0;
    v->z2 = 0;
    v->xTarget = 0;
    v->zTarget = 0;
    v->timeTracker = 0.0;
    v->speed = 0.0;

    return v;
}

void initializeVehicle(Vehicle *v, vehicle_type type, Team *t)
{
    v->colour = t->colour;
    v->state = SEARCHING_VEHICLE_STATE;
    v->xTarget = intRand(1, WORLDX - 1);
    v->zTarget = intRand(1, WORLDZ - 1);

    int canBePlaced = 0;
    int runCount = 0;
    int edgeSize = 0;

    switch (type)
    {
    case TRUCK_VEHICLE:
    {
        v->speed = TRUCK_SPEED;
        edgeSize = TRUCK_EDGE_LENGTH;
        break;
    }
    default:
        printf("ERROR: Invalid vehicle type\n");
        exit(1);
    }

    while (!canBePlaced)
    {
        switch (t->type)
        {
        case RED_TEAM:
        {
            v->x1 = t->base->x2 + VEHICLE_OFFSET - (((runCount * VEHICLE_OFFSET) % (VEHICLE_OFFSET * edgeSize)));
            v->z1 = t->base->z1 + (VEHICLE_OFFSET * runCount);
            break;
        }
        case BLUE_TEAM:
        {
            v->x1 = t->base->x1 - VEHICLE_OFFSET - (((runCount * VEHICLE_OFFSET) % (VEHICLE_OFFSET * edgeSize)));
            v->z1 = t->base->z1 + (VEHICLE_OFFSET * runCount);
            break;
        }
        default:
            printf("WARNING: invalid team type!\n");
            exit(1);
        }

        v->x2 = v->x1 + edgeSize;
        v->z2 = v->z1 + edgeSize;

        v->y = getTopPosition(v->x1, v->z1, v->x2, v->z2);

        if (!checkTeamCollision(t, v->y, v->x1, v->z1, v->x2, v->z2))
        {
            canBePlaced = 1;
        }

        runCount++;
        if (runCount > MAX_ATTEMPTS_TO_PLACE_OBJECT)
        {
            printf("WARNING: could not place vehicle, placing anyways\n");
            canBePlaced = 1;
        }
    }
}

void generateVehicle(Vehicle *v)
{
    // draw square size of vehicle edge
    for (int x = v->x1; x < v->x2; x++)
    {
        for (int z = v->z1; z < v->z2; z++)
        {
            world[x][v->y][z] = v->colour;
        }
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[v->x1][v->y][v->z1] = 4;
    // world[v->x2][v->y][v->z2] = 5;
}

void moveVehicle(Vehicle *v)
{
    switch (v->state)
    {
    case SEARCHING_VEHICLE_STATE:
    {
        // move vehicle to next position
        removeVehicle(v);
        incrementVehicle(v);
        generateVehicle(v);

        // check for meteor
        // if meteor found
        //  set new target and state
        //  break

        // position has been reached, no meteor detected, find new position
        if (v->xTarget == v->x1 && v->zTarget == v->z1)
        {
            v->xTarget = intRand(1, WORLDX - 1);
            v->zTarget = intRand(1, WORLDZ - 1);
        }

        break;
    }
    case MOVING_VEHICLE_STATE:
        /* code */
        break;
    case LOADING_VEHICLE_STATE:
        /* code */
        break;
    case RETURNING_VEHICLE_STATE:
        /* code */
        break;
    default:
        printf("ERROR: invalid vehicle state\n");
        exit(1);
    }
}

void incrementVehicle(Vehicle *v)
{
    if (v->xTarget < v->x1)
    {
        v->x1 -= 1;
        v->x2 -= 1;
    }
    else if (v->xTarget > v->x1)
    {
        v->x1 += 1;
        v->x2 += 1;
    }
    if (v->zTarget < v->z1)
    {
        v->z1 -= 1;
        v->z2 -= 1;
    }
    else if (v->zTarget > v->z1)
    {
        v->z1 += 1;
        v->z2 += 1;
    }
    v->y = getTopPosition(v->x1, v->z1, v->x2, v->z2);
}

void removeVehicle(Vehicle *v)
{
    // draw square size of vehicle edge to remove
    for (int x = v->x1; x < v->x2; x++)
    {
        for (int z = v->z1; z < v->z2; z++)
        {
            world[x][v->y][z] = 0;
        }
    }
}

void freeVehicle(Vehicle *v)
{
    free(v);
}
