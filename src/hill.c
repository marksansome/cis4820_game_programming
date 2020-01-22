
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hill.h"
#include "generation.h"

Hill *createHill()
{
    Hill *h = (Hill *)malloc(sizeof(Hill));
    if (h == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    h->radius = 0;
    h->height = 0;
    h->xCenter = 0;
    h->yCenter = 0;
    h->zCenter = 0;
    h->x1 = 0;
    h->z1 = 0;
    h->x2 = 0;
    h->z2 = 0;

    return h;
}

void initializeHill(Hill *h)
{
    h->radius = (int)(rand() % (MAX_HILL_RADIUS - MIN_HILL_RADIUS + 1)) + MIN_HILL_RADIUS;
    h->height = (rand() % (MAX_HILL_HEIGHT - MIN_HILL_HEIGHT + 1) + MIN_HILL_HEIGHT);
    h->xCenter = (rand() % (WORLDX - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;
    h->yCenter = GROUND_DEPTH;
    h->zCenter = (rand() % (WORLDZ - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;

    h->x1 = h->xCenter - h->radius;
    h->z1 = h->zCenter + h->radius;
    h->x2 = h->xCenter + h->radius;
    h->z2 = h->zCenter - h->radius;
}

void generateHill(Hill *h)
{
    for (int i = 0; i < h->height; i++)
    {
        drawCircle(h->xCenter, h->yCenter + i, h->zCenter, h->radius - i, GREEN);
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[h->x1][h->yCenter][h->z1] = 4;
    // world[h->x2][h->yCenter][h->z2] = 5;
}

void freeHill(Hill *h)
{
    free(h);
}
