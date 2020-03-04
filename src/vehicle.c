/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "linkedList.h"
#include "meteor.h"
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

    v->type = INVALID_VEHICLE;
    v->state = INVALID_VEHICLE_STATE;
    v->colour = 0;
    v->health = 0;
    v->height = 0;
    v->y = 0;
    v->x1 = 0;
    v->z1 = 0;
    v->x2 = 0;
    v->z2 = 0;
    v->xTarget = 0;
    v->zTarget = 0;
    v->isCarryingMeteor = 0;
    v->targetMeteor = NULL;
    v->timeTracker = 0.0;
    v->speed = 0.0;
    v->baseSpeed = 0.0;

    return v;
}

void initializeVehicle(Vehicle *v, vehicle_type type, Team *t)
{
    v->type = type;
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
        v->speed = TRUCK_SPEED;
        v->baseSpeed = TRUCK_SPEED;
        v->height = TRUCK_HEIGHT;
        v->health = TRUCK_HEALTH;
        edgeSize = TRUCK_EDGE_LENGTH;
        break;
    default:
        printf("ERROR: Invalid vehicle type\n");
        exit(1);
    }

    while (!canBePlaced)
    {
        switch (t->type)
        {
        case RED_TEAM:
            v->x1 = t->base->x2 + VEHICLE_OFFSET - (((runCount * VEHICLE_OFFSET) % (VEHICLE_OFFSET * edgeSize)));
            v->z1 = t->base->z1 + (VEHICLE_OFFSET * runCount);
            break;
        case BLUE_TEAM:
            v->x1 = t->base->x1 - VEHICLE_OFFSET - (((runCount * VEHICLE_OFFSET) % (VEHICLE_OFFSET * edgeSize)));
            v->z1 = t->base->z1 + (VEHICLE_OFFSET * runCount);
            break;
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

void generateVehicle(Vehicle *v, team_type teamType, int isEmpty)
{
    int tireColour = 0;
    int vehicleColour = 0;
    int meteorColour = 0;

    if (isEmpty)
    {
        tireColour = getColour(EMPTY);
        vehicleColour = getColour(EMPTY);
        meteorColour = getColour(EMPTY);
    }
    else
    {
        tireColour = getColour(VEHICLE_TIRE_COLOUR);
        vehicleColour = v->colour;
        meteorColour = getColour(DARK_GRAY);
    }
    switch (v->type)
    {
    case TRUCK_VEHICLE:
    {
        int x1 = v->x1;
        int y1 = v->y;
        int z1 = v->z1;
        int y2 = v->y + v->height - 1;

        // draw tires
        world[x1][y1][z1] = tireColour;
        world[x1 + TRUCK_EDGE_LENGTH - 1][y1][z1] = tireColour;
        world[x1][y1][z1 + TRUCK_EDGE_LENGTH - 1] = tireColour;
        world[x1 + TRUCK_EDGE_LENGTH - 1][y1][z1 + TRUCK_EDGE_LENGTH - 1] = tireColour;

        // middle
        world[x1 + 1][y2][z1 + 1] = vehicleColour;

        switch (teamType)
        {
        case RED_TEAM:
            // draw sides
            // left
            world[x1][y2][z1] = vehicleColour;
            world[x1 + 1][y2][z1] = vehicleColour;
            //right
            world[x1][y2][z1 + TRUCK_EDGE_LENGTH - 1] = vehicleColour;
            world[x1 + 1][y2][z1 + TRUCK_EDGE_LENGTH - 1] = vehicleColour;
            // front
            world[x1 + TRUCK_EDGE_LENGTH - 1][y2][z1 + 1] = vehicleColour;
            if (v->isCarryingMeteor)
            {
                world[x1][y2][z1 + 1] = meteorColour;
            }
            break;
        case BLUE_TEAM:
            // draw sides
            // left
            world[x1 + 1][y2][z1] = vehicleColour;
            world[x1 + 2][y2][z1] = vehicleColour;
            //right
            world[x1 + 1][y2][z1 + TRUCK_EDGE_LENGTH - 1] = vehicleColour;
            world[x1 + 2][y2][z1 + TRUCK_EDGE_LENGTH - 1] = vehicleColour;
            // front
            world[x1][y2][z1 + 1] = vehicleColour;
            if (v->isCarryingMeteor)
            {
                world[x1 + TRUCK_EDGE_LENGTH - 1][y2][z1 + 1] = meteorColour;
            }
            break;
        default:
            printf("WARNING: Invalid team type\n");
            exit(1);
        }
        break;
    }
    default:
        printf("ERROR: Invalid vehicle type\n");
        exit(1);
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[v->x1][v->y][v->z1] = 4;
    // world[v->x2][v->y][v->z2] = 5;
}

void moveVehicle(Vehicle *v, Team *t, List *meteors)
{
    updateVehicleDamage(v);

    //! @todo handle vehicle cleanup and explosion

    switch (v->state)
    {
    case SEARCHING_VEHICLE_STATE:
    {
        // move vehicle to next position
        generateVehicle(v, t->type, 1);
        incrementVehicle(v);
        generateVehicle(v, t->type, 0);

        // position has been reached, no meteor detected, find new position
        if (v->xTarget == v->x1 && v->zTarget == v->z1)
        {
            setSearchingState(v, t);
        }

        // check for meteor
        for (int i = 0; i < getListSize(meteors); i++)
        {
            Meteor *m = getItemAtIndex(meteors, i)->ptr;
            if ((abs(m->x - v->x1) <= VEHICLE_METEOR_RADIUS) &&
                (abs(m->z - v->z1) <= VEHICLE_METEOR_RADIUS))
            {
                if (m->isCollected == 0)
                {
                    switch (t->type)
                    {
                    case RED_TEAM:
                        v->xTarget = m->x - abs(v->x1 - v->x2);
                        v->zTarget = m->z - 1;
                        break;
                    case BLUE_TEAM:
                        v->xTarget = m->x + 1;
                        v->zTarget = m->z - 1;
                        break;
                    default:
                        printf("WARNING: invalid team type!\n");
                        exit(1);
                    }
                    v->targetMeteor = m;
                    v->state = MOVING_VEHICLE_STATE;
                    break;
                }
            }
        }
        break;
    }
    case MOVING_VEHICLE_STATE:
    {
        // move vehicle to next position
        generateVehicle(v, t->type, 1);
        incrementVehicle(v);
        generateVehicle(v, t->type, 0);

        if (v->targetMeteor->isCollected == 1)
        {
            setSearchingState(v, t);
        }

        // position has been reached, load meteor
        if (v->xTarget == v->x1 && v->zTarget == v->z1)
        {
            v->targetMeteor->isCollected = 1;
            v->state = LOADING_VEHICLE_STATE;
            v->speed = v->baseSpeed * (v->baseSpeed / 100); // set wait time proportional to movement speed
        }
        break;
    }
    case LOADING_VEHICLE_STATE:
    {
        // reset speed after loading
        v->speed = v->baseSpeed;

        // remove meteor from the world
        removeMeteor(v->targetMeteor);

        // update vehicle
        v->state = RETURNING_VEHICLE_STATE;

        switch (t->type)
        {
        case RED_TEAM:
            v->xTarget = t->base->x2 + 1;
            v->zTarget = t->base->z1 - (BASE_EDGE_LENGTH / 2);
            break;
        case BLUE_TEAM:
            v->xTarget = t->base->x1 - 1 - abs(v->x1 - v->x2);
            v->zTarget = t->base->z1 - (BASE_EDGE_LENGTH / 2);
            break;
        default:
            printf("WARNING: invalid team type!\n");
            exit(1);
        }
        break;
    }
    case RETURNING_VEHICLE_STATE:
    {
        v->isCarryingMeteor = 1;

        // move vehicle to next position
        generateVehicle(v, t->type, 1);
        incrementVehicle(v);
        generateVehicle(v, t->type, 0);

        // position has been reached, offload meteor
        if (v->xTarget == v->x1 && v->zTarget == v->z1)
        {
            // add meteor to team
            Meteor *m = removeMeteorFromList(v->targetMeteor, meteors);
            addItem(t->meteors, m, METEOR);
            setSearchingState(v, t);
        }
        break;
    }
    default:
        printf("ERROR: invalid vehicle state\n");
        exit(1);
    }
}

void setSearchingState(Vehicle *v, Team *t)
{
    generateVehicle(v, t->type, 1);
    v->state = SEARCHING_VEHICLE_STATE;
    v->xTarget = intRand(1, WORLDX - 1);
    v->zTarget = intRand(1, WORLDZ - 1);
    v->isCarryingMeteor = 0;
    v->targetMeteor = NULL;
    generateVehicle(v, t->type, 0);
}

void incrementVehicle(Vehicle *v)
{
    //! @todo need to add collision detection here
    // the miss in collision happens when the vehicle tries to move up
    // but the next car is there?
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

void updateVehicleDamage(Vehicle *v)
{
    // check the number of blocks in vehicle
    // if count is less than expected, damage
    int blockCount = 0;
    int expectedCount = 0;

    for (int y = v->y; y < v->y + v->height; y++)
    {
        for (int x = v->x1; x < v->x2; x++)
        {
            for (int z = v->z1; z < v->z2; z++)
            {
                if (world[x][y][z] != 0)
                {
                    blockCount++;
                }
            }
        }
    }

    switch (v->type)
    {
    case TRUCK_VEHICLE:
        expectedCount = TRUCK_BLOCK_COUNT;
        break;
    default:
        printf("ERROR: Invalid vehicle type\n");
        exit(1);
    }

    if (v->isCarryingMeteor)
    {
        expectedCount++;
    }

    if (blockCount < expectedCount)
    {
        v->health -= 1;
        printf("vehicle took damage\n");
        world[v->x1][v->y + 5][v->z1] = getColour(YELLOW);
    }
}

void removeVehicle(Vehicle *v)
{
    /**
     * @note this remove the entire square of the vehicle
     * if the vehicle has a spot another vehicle could clime on top of
     * it will be removes in this.
     */
    // remove square size of vehicle edge to remove
    // for (int y = v->y; y < v->y + v->height; y++)
    // {
    //     for (int x = v->x1; x < v->x2; x++)
    //     {
    //         for (int z = v->z1; z < v->z2; z++)
    //         {
    //             world[x][y][z] = 0;
    //         }
    //     }
    // }
}

// for (int x = x1; x < x2; x++)
// {
//     for (int z = z1; z < z2; z++)
//     {
//         // for (int y = CLOUD_LEVEL - 1; y > 0; y--)
//         for (int y = 0; y < (CLOUD_LEVEL - 1); y++)

void freeVehicle(Vehicle *v)
{
    free(v);
}
