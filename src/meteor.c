/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "meteor.h"

#include "config.h"
#include "graphics.h"

Meteor *createMeteor()
{
    Meteor *m = (Meteor *)malloc(sizeof(Meteor));
    if (m == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    m->x = 0;
    m->y = 0;
    m->z = 0;
    m->xLand = 0;
    m->yLand = 0;
    m->zLand = 0;
    m->xStart = 0;
    m->yStart = 0;
    m->zStart = 0;
    m->xDir = 0;
    m->zDir = 0;
    m->isFalling = 1;

    return m;
}

void initMeteor(Meteor *m)
{
    m->x = (rand() % (WORLDX - (2 * 5) - 1)) + 5;

    // h->yCenter = GROUND_DEPTH;
    // h->zCenter = (rand() % (WORLDZ - (2 * MAX_HILL_RADIUS) - 1)) + MAX_HILL_RADIUS;

    // b->z1 = (rand() % (WORLDZ - (2 * BASE_EDGE_LENGTH) - 1)) + BASE_EDGE_LENGTH;
}

// void generateBase(Base *b)
// {
//     // draw square size of base edge
//     for (int y = b->y1; y <= b->y2; y++)
//     {
//         for (int x = b->x1; x <= b->x2; x++)
//         {
//             for (int z = b->z1; z >= b->z2; z--)
//             {
//                 world[x][y][z] = b->colour;
//             }
//         }
//     }

//     // debug: show square (x1,z1) (x2,z2)
//     // world[b->x1][b->y2][b->z1] = 4;
//     // world[b->x2][b->y2][b->z2] = 5;
// }
