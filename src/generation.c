#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"

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
    //red
    Base *b1 = createBase();
    initializeBase(b1, 2, 15);
    Structure *sb1 = createStructure(id_base, 1, b1);
    addGameObject(sb1);
    //blue
    Base *b2 = createBase();
    initializeBase(b2, 3, 75);
    Structure *sb2 = createStructure(id_base, 1, b2);
    addGameObject(sb2);

    for (int i = 0; i < MAX_TERRAIN; i++)
    {
        // alternate between generating valleys and hills
        if ((i % 2) != 0) //valley
        {
            Valley *v = createValley();
            initializeValley(v);

            if (!checkCircleStructureCollision(-1, v->x, v->z, v->radius))
            {
                Structure *s = createStructure(id_valley, 1, v);
                addGameObject(s);
            }
        }
        else //hill
        {
            Hill *h = createHill();
            initializeHill(h);

            if (!checkCircleStructureCollision(-1, h->x, h->z, h->radius))
            {
                Structure *s = createStructure(id_hill, 1, h);
                addGameObject(s);
            }
        }
    }

    //TODO: collision. if valley can be placed

    // place generated objects into world
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
                generateValley(v);
                break;
            }
            case id_hill:
            {
                Hill *h = s->ptr;
                generateHill(h);
                break;
            }
            case id_base:
            {
                Base *b = s->ptr;
                generateBase(b);
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

void addGameObject(Structure *s)
{
    gameObjects->structures[gameObjects->numStructures] = s;
    gameObjects->numStructures += 1;
}

int checkCircleStructureCollision(int i, int x, int z, int r)
{
    int isCollision = 0;

    // Note: object 1 is A, object 2 is B
    for (int j = 0; j < gameObjects->numStructures; j++)
    {
        if (isCollision)
        {
            break;
        }

        // Collision is with itself or similar typed object
        if (i == j)
        {
            isCollision = 0;
        }

        int x1A, x2A, z1A, z2A = 0;
        int x1B, x2B, z1B, z2B = 0;
        Structure *s = gameObjects->structures[j];

        // get top left and bottom right coords of object
        x1A = x - r;
        x2A = x + r;
        z1A = z + r;
        z2A = z - r;

        if (s->id == id_base)
        {
            Base *b = s->ptr;

            // get top left and bottom right coords of object
            x1B = b->x;
            x2B = b->x + b->length;
            z1B = b->z;
            z2B = b->z + b->width;
        }
        else
        {
            // get a structures x, z, radius
            int xb, zb, rb = 0;
            getStructureXZR(j, &xb, &zb, &rb);

            // get top left and bottom right coords of object
            x1B = xb - rb;
            x2B = xb + rb;
            z1B = zb + rb;
            z2B = zb - rb;
        }

        if (x1A <= x2B && x2A >= x1B && z1A >= z2B && z2A <= z1B)
        {
            isCollision = 1;
        }
    }

    return (isCollision);
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
