#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generation.h"

GameObjects *gameObjects;

CloudObjects *cloudObjects;

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

void initializeGameObjects()
{
    gameObjects = (GameObjects *)malloc(sizeof(GameObjects));
    if (gameObjects == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    gameObjects->numStructures = 0;
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        gameObjects->structures[i] = NULL;
    }
}

void initializeCloudObjects()
{
    cloudObjects = (CloudObjects *)malloc(sizeof(CloudObjects));
    if (cloudObjects == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    cloudObjects->numClouds = 0;
    for (int i = 0; i < MAX_CLOUDS; i++)
    {
        cloudObjects->clouds[i] = NULL;
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
    addGameObject(createStructure(id_base, 1, bRed));
    // blue
    Base *bBlue = createBase();
    initializeBase(bBlue, 3, 75);
    addGameObject(createStructure(id_base, 1, bBlue));

    for (int i = 0; i < MAX_TERRAIN; i++)
    {
        // alternate between generating valleys and hills
        if ((i % 2) != 0) //valley
        {
            Valley *v = createValley();
            initializeValley(v);

            if (!checkStructureCollision(-1, v->x1, v->z1, v->x2, v->z2))
            {
                addGameObject(createStructure(id_valley, 1, v));
            }
        }
        else //hill
        {
            Hill *h = createHill();
            initializeHill(h);

            if (!checkStructureCollision(-1, h->x1, h->z1, h->x2, h->z2))
            {
                addGameObject(createStructure(id_hill, 1, h));
            }
        }
    }

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

                generateValley((Valley *)s->ptr);
                break;
            }
            case id_hill:
            {
                generateHill((Hill *)s->ptr);
                break;
            }
            case id_base:
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
        cloudObjects->clouds[cloudObjects->numClouds] = c;
        cloudObjects->numClouds += 1;
        generateCloud(c);
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

int checkStructureCollision(int index, int x1, int z1, int x2, int z2)
{
    int isCollision = 0;
    for (int i = 0; i < gameObjects->numStructures; i++)
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
    if (index >= gameObjects->numStructures)
    {
        printf("ERROR: Out Of Bounds. Trying to access gameObject outside of array\n");
        return 1;
    }

    Structure *s = gameObjects->structures[index];
    switch (s->id)
    {
    case id_valley:
    {
        Valley *v = s->ptr;
        *x1 = v->x1;
        *z1 = v->z1;
        *x2 = v->x2;
        *z2 = v->z2;
        break;
    }
    case id_hill:
    {
        Hill *h = s->ptr;
        *x1 = h->x1;
        *z1 = h->z1;
        *x2 = h->x2;
        *z2 = h->z2;
        break;
    }
    case id_base:
    {
        Base *b = s->ptr;
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

void freeStructures()
{
    //TODO: handle freeing memory. Call each objects free
    return;
}

// int checkCircleStructureCollision(int i, int x, int z, int r)
// {
//     int isCollision = 0;

//     // Note: object 1 is A, object 2 is B
//     for (int j = 0; j < gameObjects->numStructures; j++)
//     {
//         if (isCollision)
//         {
//             break;
//         }

//         // Collision is with itself or similar typed object
//         if (i == j)
//         {
//             isCollision = 0;
//         }

//         int x1A, x2A, z1A, z2A = 0;
//         int x1B, x2B, z1B, z2B = 0;
//         Structure *s = gameObjects->structures[j];

//         // get top left and bottom right coords of object
//         x1A = x - r;
//         x2A = x + r;
//         z1A = z + r;
//         z2A = z - r;

//         if (s->id == id_base)
//         {
//             Base *b = s->ptr;

//             // get top left and bottom right coords of object
//             x1B = b->x1;
//             x2B = b->x1 + BASE_EDGE_LENGTH;
//             z1B = b->z1;
//             z2B = b->z1 + BASE_EDGE_LENGTH;
//         }
//         else
//         {
//             // get a structures x, z, radius
//             int xb, zb, rb = 0;
//             getStructureXZR(j, &xb, &zb, &rb);

//             // get top left and bottom right coords of object
//             x1B = xb - rb;
//             x2B = xb + rb;
//             z1B = zb + rb;
//             z2B = zb - rb;
//         }

//         if (x1A <= x2B && x2A >= x1B && z1A >= z2B && z2A <= z1B)
//         {
//             isCollision = 1;
//         }
//     }

//     return (isCollision);
// }

// int getStructureXZR(int index, int *x, int *z, int *r)
// {
//     if (index >= gameObjects->numStructures)
//     {
//         printf("ERROR: Out Of Bounds. Trying to access gameObject outside of array\n");
//         return (1);
//     }
//     Structure *s = gameObjects->structures[index];
//     switch (s->id)
//     {
//     case id_valley:
//     {
//         Valley *v = s->ptr;
//         *x = v->xCenter;
//         *z = v->zCenter;
//         *r = v->radius;
//         break;
//     }
//     case id_hill:
//     {
//         Hill *h = s->ptr;
//         *x = h->xCenter;
//         *z = h->zCenter;
//         *r = h->radius;
//         break;
//     }
//     case id_base:
//     {
//         //add generation for bases
//         // Base *b = b->ptr;
//         // *x = b->x;
//         // *z = b->z;
//         // *r = b->radius;
//         break;
//     }
//     default:
//     {
//         printf("ERROR: Invalid structure ID\n");
//         return (1);
//     }
//     }
//     return (0);
// }
