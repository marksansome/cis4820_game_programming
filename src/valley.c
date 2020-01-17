
#include "valley.h"
#include "generation.h"

void initializeValley(Valley *vall)
{
    vall->radius = (int)(rand() % (MAX_VALLEY_RADIUS - MIN_VALLEY_RADIUS + 1)) + MIN_VALLEY_RADIUS;
    vall->x = (rand() % (WORLDX - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;
    vall->z = (rand() % (WORLDZ - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;
}

void generateValley(Valley vall)
{
    for (int i = 0; i < VALLEY_DEPTH; i++)
    {
        drawCircle(vall.x, GROUND_DEPTH - 1 - i, vall.z, vall.radius - i, 0);
    }
}