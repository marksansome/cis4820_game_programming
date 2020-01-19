
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hill.h"
#include "generation.h"

void initializeHill(Hill *hill)
{
    hill->radius = (int)(rand() % (MAX_HILL_RADIUS - MIN_HILL_RADIUS + 1)) + MIN_HILL_RADIUS;
    hill->x = (rand() % (WORLDX - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;
    hill->z = (rand() % (WORLDZ - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;
}

void generateHill(Hill hill)
{
    for (int i = 0; i < HILL_DEPTH; i++)
    {
        drawCircle(hill.x, GROUND_DEPTH + i, hill.z, hill.radius - i, 10);
    }
}