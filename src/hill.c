
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
    h->x = 0;
    h->z = 0;

    return h;
}

void initializeHill(Hill *h)
{
    h->radius = (int)(rand() % (MAX_HILL_RADIUS - MIN_HILL_RADIUS + 1)) + MIN_HILL_RADIUS;
    h->x = (rand() % (WORLDX - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;
    h->z = (rand() % (WORLDZ - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;
}

void generateHill(Hill *h)
{
    for (int i = 0; i < HILL_DEPTH; i++)
    {
        drawCircle(h->x, GROUND_DEPTH + i, h->z, h->radius - i, 10);
    }
}

void freeHill(Hill *h)
{
    free(h);
}
