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
#include "linkedList.h"

#include "base.h"
#include "cloud.h"
#include "hill.h"
#include "meteor.h"
#include "team.h"
#include "utility.h"
#include "valley.h"
#include "vehicle.h"

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
    Base *rBase = createBase();
    initializeBase(rBase, g_red_team->colour, getTeamOffset(g_red_team->type));
    addItem(g_structures, rBase, BASE);
    g_red_team->base = rBase;

    Base *bBase = createBase();
    initializeBase(bBase, g_blue_team->colour, getTeamOffset(g_blue_team->type));
    addItem(g_structures, bBase, BASE);
    g_blue_team->base = bBase;

    for (int i = 0; i < MAX_TERRAIN; i++)
    {
        // alternate between generating valleys and hills
        if ((i % 2) != 0) //valley
        {
            Valley *v = createValley();
            initializeValley(v);

            if (!checkCollision(g_structures, -1, v->x1, v->z1, v->x2, v->z2))
            {
                addItem(g_structures, v, VALLEY);
            }
        }
        else //hill
        {
            Hill *h = createHill();
            initializeHill(h);

            if (!checkCollision(g_structures, -1, h->x1, h->z1, h->x2, h->z2))
            {
                addItem(g_structures, h, HILL);
            }
        }
    }

    // place generated objects into world
    for (int i = 0; i < getListSize(g_structures); i++)
    {
        Item *s = getItemAtIndex(g_structures, i);
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
            printf("WARNING: Invalid structure ID\n");
            break;
        }
        }
    }

    // add team starting objects
    initializeTeamStartingObjects(g_red_team);
    initializeTeamStartingObjects(g_blue_team);

    // generate clouds
    for (int i = 0; i < MAX_CLOUDS; i++)
    {
        Cloud *c = createCloud();
        initializeCloud(c);
        addItem(g_clouds, c, CLOUD);
        generateCloud(c);
    }

    // add starter meteors
    for (int i = 0; i < STARTING_METEORS; i++)
    {
        Meteor *m = createMeteor();
        initializeMeteor(m);
        addItem(g_falling_meteors, m, METEOR);
    }

    // set player starting positon
    setViewPosition(-50, -20, -50);
}
