/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generation.h"

#include "config.h"
#include "data.h"
#include "graphics.h"

#include "base.h"
#include "cloud.h"
#include "hill.h"
#include "utility.h"
#include "valley.h"

void createTestWorld()
{
    /* some sample objects */
    /* build a red platform */
    for (int i = 0; i < WORLDX; i++)
    {
        for (int j = 0; j < WORLDZ; j++)
        {
            world[i][24][j] = 3;
        }
    }
    /* create some green and blue cubes */
    world[50][25][50] = 1;
    world[49][25][50] = 1;
    world[49][26][50] = 1;
    world[52][25][52] = 2;
    world[52][26][52] = 2;

    /* create user defined colour and draw cube */
    // colour is now created in createUserColours()
    world[54][25][50] = 9;

    /* blue box shows xy bounds of the world */
    for (int i = 0; i < WORLDX - 1; i++)
    {
        world[i][25][0] = 2;
        world[i][25][WORLDZ - 1] = 2;
    }
    for (int i = 0; i < WORLDZ - 1; i++)
    {
        world[0][25][i] = 2;
        world[WORLDX - 1][25][i] = 2;
    }

    /* create two sample mobs */
    /* these are animated in the update() function */
    createMob(0, 50.0, 25.0, 52.0, 0.0);
    createMob(1, 50.0, 25.0, 52.0, 0.0);

    /* create sample player */
    createPlayer(0, 52.0, 27.0, 52.0, 0.0);
}

void createMainWorld()
{
    // place initial floor
    for (int y = 0; y < GROUND_DEPTH; y++)
    {
        for (int x = 0; x < WORLDX; x++)
        {
            for (int z = 0; z < WORLDZ; z++)
            {
                // set top layer of ground to green, rest to brown
                if (y == (GROUND_DEPTH - 1))
                {
                    // green
                    world[x][y][z] = getColour(GREEN);
                }
                else
                {
                    // brown
                    world[x][y][z] = getColour(BROWN);
                }
            }
        }
    }

    // add team bases
    // red
    Base *bRed = createBase();
    initializeBase(bRed, 2, 15);
    addStructure(createObject(BASE, 1, bRed));

    // blue
    Base *bBlue = createBase();
    initializeBase(bBlue, 3, 75);
    addStructure(createObject(BASE, 1, bBlue));

    for (int i = 0; i < MAX_TERRAIN; i++)
    {
        // alternate between generating valleys and hills
        if ((i % 2) != 0) //valley
        {
            Valley *v = createValley();
            initializeValley(v);

            if (!checkStructureCollision(-1, v->x1, v->z1, v->x2, v->z2))
            {
                addStructure(createObject(VALLEY, 1, v));
            }
        }
        else //hill
        {
            Hill *h = createHill();
            initializeHill(h);

            if (!checkStructureCollision(-1, h->x1, h->z1, h->x2, h->z2))
            {
                addStructure(createObject(HILL, 1, h));
            }
        }
    }

    // place generated objects into world
    for (int i = 0; i < g_structures->numObj; i++)
    {
        if (g_structures->object[i]->render)
        {
            Object *s = g_structures->object[i];
            switch (s->type)
            {
            case VALLEY:
            {

                generateValley((Valley *)s->ptr);
                break;
            }
            case HILL:
            {
                generateHill((Hill *)s->ptr);
                break;
            }
            case BASE:
            {
                generateBase((Base *)s->ptr);
                break;
            }
            default:
            {
                printf("ERROR: Invalid structure ID\n");
                break;
            }
            }
        }
    }

    // generate clouds
    for (int i = 0; i < MAX_CLOUDS; i++)
    {
        Cloud *c = createCloud();
        initializeCloud(c);
        addCloud(createObject(CLOUD, 1, c));
        generateCloud(c);
    }

    // set player starting positon
    setViewPosition(-50, -20, -50);
}

int checkStructureCollision(int index, int x1, int z1, int x2, int z2)
{
    int isCollision = 0;
    for (int i = 0; i < g_structures->numObj; i++)
    {
        if (isCollision)
        {
            break;
        }

        // get next structures (x1, z1) (x2, z2)
        int x1b, z1b, x2b, z2b = 0;
        getStructureSquare(i, &x1b, &z1b, &x2b, &z2b);

        if (x1 <= x2b && x2 >= x1b && z1 >= z2b && z2 <= z1b)
        {
            isCollision = 1;
        }

        // collision is with itself, ignore
        if (i == index)
        {
            isCollision = 0;
        }
    }

    return isCollision;
}

int getStructureSquare(int index, int *x1, int *z1, int *x2, int *z2)
{
    if (index >= g_structures->numObj)
    {
        printf("ERROR: Out Of Bounds. Trying to access g_structures outside of array\n");
        return 1;
    }

    Object *o = g_structures->object[index];
    switch (o->type)
    {
    case VALLEY:
    {
        Valley *v = o->ptr;
        *x1 = v->x1;
        *z1 = v->z1;
        *x2 = v->x2;
        *z2 = v->z2;
        break;
    }
    case HILL:
    {
        Hill *h = o->ptr;
        *x1 = h->x1;
        *z1 = h->z1;
        *x2 = h->x2;
        *z2 = h->z2;
        break;
    }
    case BASE:
    {
        Base *b = o->ptr;
        *x1 = b->x1;
        *z1 = b->z1;
        *x2 = b->x2;
        *z2 = b->z2;
        break;
    }
    default:
    {
        printf("ERROR: Invalid structure ID\n");
        return (1);
    }
    }
    return (0);
}
