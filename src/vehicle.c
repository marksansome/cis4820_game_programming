/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
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
    v->y = 0;
    v->x1 = 0;
    v->z1 = 0;
    v->x2 = 0;
    v->z2 = 0;

    return v;
}

void initializeVehicle(Vehicle *v, int colour, int vehiclePos)
{
    v->colour = colour;

    v->y = GROUND_DEPTH;
    v->x1 = vehiclePos;
    v->z1 = (rand() % (WORLDZ - (2 * VEHICLE_EDGE_LENGTH) - 1)) + VEHICLE_EDGE_LENGTH;
    v->x2 = v->x1 + VEHICLE_EDGE_LENGTH;
    v->z2 = v->z1 - VEHICLE_EDGE_LENGTH;
}

void generateVehicle(Vehicle *v)
{
    // draw square size of vehicle edge
    for (int x = v->x1; x < v->x2; x++)
    {
        for (int z = v->z1; z > v->z2; z--)
        {
            world[x][v->y][z] = v->colour;
        }
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[v->x1][v->y][v->z1] = 4;
    // world[v->x2][v->y][v->z2] = 5;
}

void freeVehicle(Vehicle *v)
{
    free(v);
}
