#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"
#include "hill.h"
#include "valley.h"

GameObjects *gameObjects;

void initializeWorld()
{
    /* initialize world to empty */
    for (int i = 0; i < WORLDX; i++)
    {
        for (int j = 0; j < WORLDY; j++)
        {
            for (int k = 0; k < WORLDZ; k++)
            {
                world[i][j][k] = 0;
            }
        }
    }
}

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
    /* Intializes random number generator */
    time_t t;
    srand((unsigned)time(&t));

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
                    world[x][y][z] = 10;
                }
                else
                {
                    // brown
                    world[x][y][z] = 11;
                }
            }
        }
    }

    // add team bases

    // add valleys
    for (int i = 0; i < NUM_VALLEYS; i++)
    {
        Valley *v = createValley();
        initializeValley(v);

        Structure *s = createStructure(id_valley, 1, v);

        // if (checkStructureCollision(v->x, v->z, v->radius))
        // {
        //     initializeValley(v);
        //     if (checkStructureCollision(v->x, v->z, v->radius))
        //     {
        //         continue;
        //     }
        // }

        gameObjects->structures[gameObjects->numStructures] = s;
        gameObjects->numStructures += 1;
    }

    // add hills
    for (int i = 0; i < NUM_HILLS; i++)
    {
        Hill *h = createHill();
        initializeHill(h);

        Structure *s = createStructure(id_hill, 1, h);

        // check for collision with other structures
        // if (checkStructureCollision(h->x, h->z, h->radius))
        // {
        //     initializeHill(h);
        //     if (checkStructureCollision(h->x, h->z, h->radius))
        //     {
        //         continue;
        //     }
        // }

        gameObjects->structures[gameObjects->numStructures] = s;
        gameObjects->numStructures += 1;
    }

    //TODO: collision. if valley can be placed

    for (int i = 0; i < gameObjects->numStructures; i++)
    {
        if (gameObjects->structures[i]->render)
        {
            Structure *s = gameObjects->structures[i];
            switch (s->id)
            {
            case id_valley:
            {
                Valley *v = s->ptr;
                // if (checkStructureCollision(i, v->x, v->z, v->radius))
                // {
                //     s->render = 0;
                // }
                // else
                // {
                generateValley(v);
                // }
                break;
            }
            case id_hill:
            {
                Hill *h = s->ptr;
                // if (checkStructureCollision(i, h->x, h->z, h->radius))
                // {
                //     s->render = 0;
                // }
                // else
                // {
                generateHill(h);
                // }
                break;
            }
            case id_base:
            {
                //TODO: add generation for bases
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

    // set player starting positon
    setViewPosition(-50, -20, -50);
}

Structure *createStructure(StructureId id, int render, void *ptr)
{
    Structure *s = (Structure *)malloc(sizeof(Structure));
    if (s == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    s->id = id;
    s->render = render;
    s->ptr = ptr;

    return s;
}

int checkStructureCollision(int i, int x, int z, int r)
{
    // Note: object 1 is A, object 2 is B
    for (int j = 0; j < gameObjects->numStructures; j++)
    {
        // get a structures x, z, radius
        int xb, zb, rb = 0;
        getStructureXZR(j, &xb, &zb, &rb);

        // check if B structure collides with A x, z, radius
        // get top left and bottom right coords of each object
        int x1A = x - r;
        int x2A = x + r;
        int z1A = z + r;
        int z2A = z - r;

        int x1B = xb - rb;
        int x2B = xb + rb;
        int z1B = zb + rb;
        int z2B = zb - rb;

        if (x1A <= x2B && x2A >= x1B && z1A >= z2B && z2A <= z1B)
        {
            if (i == j)
            {
                // Collision is with itself
                return (0);
            }
            return (1);
        }
    }

    return (0);
}

int getStructureXZR(int index, int *x, int *z, int *r)
{
    if (index >= gameObjects->numStructures)
    {
        printf("ERROR: Out Of Bounds. Trying to access gameObject outside of array\n");
        return (1);
    }
    Structure *s = gameObjects->structures[index];
    switch (s->id)
    {
    case id_valley:
    {
        Valley *v = s->ptr;
        *x = v->x;
        *z = v->z;
        *r = v->radius;
        break;
    }
    case id_hill:
    {
        Hill *h = s->ptr;
        *x = h->x;
        *z = h->z;
        *r = h->radius;
        break;
    }
    case id_base:
    {
        //TODO: add generation for bases
        // Base *b = b->ptr;
        // *x = b->x;
        // *z = b->z;
        // *r = b->radius;
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

void freeStructures()
{
    //TODO: handle freeing memory. Call each objects free
    return;
}
