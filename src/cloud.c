/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "cloud.h"
#include "config.h"
#include "graphics.h"
#include "utility.h"

Cloud *createCloud()
{
    Cloud *c = (Cloud *)malloc(sizeof(Cloud));
    if (c == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    c->colour = 0;
    c->radius = 0;
    c->xCenter = 0;
    c->yCenter = 0;
    c->zCenter = 0;

    return c;
}

void initializeCloud(Cloud *c)
{
    c->colour = getColour(WHITE);
    c->radius = (int)(rand() % (MAX_CLOUD_RADIUS - MIN_CLOUD_RADIUS + 1)) + MIN_CLOUD_RADIUS;
    c->xCenter = (rand() % (WORLDX - (2 * MAX_CLOUD_RADIUS) - 1)) + MAX_CLOUD_RADIUS;
    c->yCenter = CLOUD_LEVEL;
    c->zCenter = (rand() % (WORLDZ - (2 * MAX_CLOUD_RADIUS) - 1)) + MAX_CLOUD_RADIUS;
}

void generateCloud(Cloud *c)
{
    drawCircle(c->xCenter, c->yCenter, c->zCenter, c->radius, WHITE);
}

void removeCloud(Cloud *c)
{
    drawCircle(c->xCenter, c->yCenter, c->zCenter, c->radius, EMPTY);
}

void moveCloud(Cloud *c)
{
    c->xCenter += 1;

    if ((c->xCenter) > WORLDX - 1)
    {
        c->xCenter = 0;
    }
    generateCloud(c);
}

void freeCloud(Cloud *c)
{
    free(c);
}
