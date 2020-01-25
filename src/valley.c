/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

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
    v->depth = 0;
    v->xCenter = 0;
    v->yCenter = 0;
    v->zCenter = 0;
    v->x1 = 0;
    v->z1 = 0;
    v->x2 = 0;
    v->z2 = 0;

    return v;
}

void initializeValley(Valley *v)
{
    v->radius = (int)(rand() % (MAX_VALLEY_RADIUS - MIN_VALLEY_RADIUS + 1)) + MIN_VALLEY_RADIUS;
    v->depth = (rand() % (MAX_VALLEY_DEPTH - MIN_VALLEY_DEPTH + 1) + MIN_VALLEY_DEPTH);
    v->xCenter = (rand() % (WORLDX - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;
    v->yCenter = GROUND_DEPTH - 1;
    v->zCenter = (rand() % (WORLDZ - (2 * MAX_VALLEY_RADIUS) - 1)) + MAX_VALLEY_RADIUS;

    v->x1 = v->xCenter - v->radius;
    v->z1 = v->zCenter + v->radius;
    v->x2 = v->xCenter + v->radius;
    v->z2 = v->zCenter - v->radius;
}

void generateValley(Valley *v)
{
    for (int i = 0; i < v->depth; i++)
    {
        drawCircle(v->xCenter, v->yCenter - i, v->zCenter, v->radius - i, EMPTY);
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[v->x1][v->yCenter][v->z1] = 4;
    // world[v->x2][v->yCenter][v->z2] = 5;
}

void freeValley(Valley *v)
{
    free(v);
}
