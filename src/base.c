/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "base.h"
#include "generation.h"

Base *createBase()
{
    Base *b = (Base *)malloc(sizeof(Base));
    if (b == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    b->colour = 0;
    b->height = 0;
    b->x1 = 0;
    b->z1 = 0;
    b->y1 = 0;
    b->x2 = 0;
    b->z2 = 0;
    b->y2 = 0;

    return b;
}

void initializeBase(Base *b, int colour, int basePos)
{
    b->colour = colour;
    b->height = BASE_HEIGHT;

    b->x1 = basePos;
    b->y1 = GROUND_DEPTH;
    b->z1 = (rand() % (WORLDZ - (2 * BASE_EDGE_LENGTH) - 1)) + BASE_EDGE_LENGTH;
    b->x2 = b->x1 + BASE_EDGE_LENGTH;
    b->y2 = b->y1 + b->height;
    b->z2 = b->z1 - BASE_EDGE_LENGTH;
}

void generateBase(Base *b)
{
    // draw square size of base edge
    for (int y = b->y1; y <= b->y2; y++)
    {
        for (int x = b->x1; x <= b->x2; x++)
        {
            for (int z = b->z1; z >= b->z2; z--)
            {
                world[x][y][z] = b->colour;
            }
        }
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[b->x1][b->y2][b->z1] = 4;
    // world[b->x2][b->y2][b->z2] = 5;
}

void freeBase(Base *v)
{
    free(v);
}
