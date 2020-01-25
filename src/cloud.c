/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cloud.h"
#include "generation.h"

Cloud *createCloud()
{
    Cloud *c = (Cloud *)malloc(sizeof(Cloud));
    if (c == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    c->colour = 0;
    c->x = 0;
    c->y = 0;
    c->z = 0;

    return c;
}

void initializeCloud(Cloud *c)
{
    c->colour = getColour(WHITE);
    c->x = (rand() % (WORLDX - 1) + 1);
    c->y = CLOUD_LEVEL;
    c->z = (rand() % (WORLDZ - 1) + 1);
}

void generateCloud(Cloud *c)
{
    world[c->x][c->y][c->z] = c->colour;
}

int moveCloud(Cloud *c, int speed)
{
    int oldX = c->x;
    if ((c->x + 1) >= WORLDX - 1)
    {
        c->x = 0;
    }
    else
    {
        c->x += speed;
    }
    return oldX;
}

void freeCloud(Cloud *c)
{
    free(c);
}
