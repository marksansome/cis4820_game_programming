/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "tower.h"
#include "utility.h"

Tower *createTower()
{
    Tower *t = (Tower *)malloc(sizeof(Tower));
    if (t == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    t->colour = 0;
    t->height = 0;
    t->x1 = 0;
    t->z1 = 0;
    t->x2 = 0;
    t->z2 = 0;
    t->y = 0;

    return t;
}

void initializeTower(Tower *t, int colour, int towerPos)
{
    t->colour = colour;
    t->height = BASE_HEIGHT;

    t->x1 = towerPos;
    t->z1 = intRand((WORLDZ - (2 * TOWER_EDGE_LENGTH) - 1 - BASE_STORAGE_Z_OFFSET), TOWER_EDGE_LENGTH + BASE_STORAGE_Z_OFFSET);
    t->x2 = t->x1 + TOWER_EDGE_LENGTH;
    t->z2 = t->z1 + TOWER_EDGE_LENGTH;
    t->y = GROUND_DEPTH;
}

void generateTower(Tower *t)
{
    // draw square size of base edge
    for (int y = t->y; y <= t->height; y++)
    {
        for (int x = t->x1; x < t->x2; x++)
        {
            for (int z = t->z1; z > t->z2; z--)
            {
                world[x][y][z] = t->colour;
            }
        }
    }

    // debug: show square (x1,z1) (x2,z2)
    // world[b->x1][b->y1][b->z1] = 7;
    // world[b->x2][b->y2][b->z2] = 8;
}

void freeTower(Tower *t)
{
    free(t);
}
