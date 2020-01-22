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

    b->width = BASE_WIDTH;
    b->length = BASE_LENGTH;
    b->height = BASE_HEIGHT;
    b->x = 0;
    b->z = 0;
    b->y = GROUND_DEPTH + 1;

    return b;
}

void initializeBase(Base *b, int colour, int basePos)
{
    b->x = basePos;
    b->z = (rand() % (WORLDZ - (2 * b->width) - 1)) + b->width;
    b->colour = colour;
}

void generateBase(Base *b)
{
    // draw centre block
    world[b->x][b->y][b->z] = b->colour;

    // draw square size of base edge
    // for (int y = b->y; y <= b->height; y++)
    // {
    for (int x = 0; x <= b->length; x++)
    {
        for (int z = 0; z <= b->width; z++)
        {
            world[b->x + x][b->y][b->z + z] = b->colour;
        }
    }
    // }
}

void freeBase(Base *v)
{
    free(v);
}
