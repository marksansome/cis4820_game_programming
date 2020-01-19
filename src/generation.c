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

        // if valley can be placed, add structure to main list
        generateValley(v);
        gameObjects->structures[gameObjects->numStructures] = s;
        gameObjects->numStructures += 1;
    }

    // Valley *test = gameObjects->structures[0]->ptr;
    // printf("Test valley 1 at x = %i, z = %i\n", test->x, test->z);

    // add hills
    for (int i = 0; i < NUM_HILLS; i++)
    {
        Hill *h = createHill();
        initializeHill(h);

        Structure *s = createStructure(id_hill, 1, h);

        generateHill(h);
        gameObjects->structures[gameObjects->numStructures] = h;
        gameObjects->numStructures += 1;
        // printf("Hill gen at x = %i, z = %i\n", hill.x, hill.z);
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

void freeStructures()
{
    //TODO: handle freeing memory. Call each objects free
    return;
}
