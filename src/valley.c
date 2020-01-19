
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "valley.h"
#include "generation.h"

Valley *createValley()
{
    Valley *v = (Valley *)malloc(sizeof(Valley));
    if (v == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    v->radius = 0;
    v->x = 0;
    v->z = 0;

    return v;
}

void initializeValley(Valley *v)
{
    v->radius = (int)(rand() % (MAX_VALLEY_RADIUS - MIN_VALLEY_RADIUS + 1)) + MIN_VALLEY_RADIUS;
    v->x = (rand() % (WORLDX - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;
    v->z = (rand() % (WORLDZ - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;
}

void generateValley(Valley *v)
{
    for (int i = 0; i < VALLEY_DEPTH; i++)
    {
        drawCircle(v->x, GROUND_DEPTH - 1 - i, v->z, v->radius - i, 0);
    }
}

void freeValley(Valley *v)
{
    free(v);
}
