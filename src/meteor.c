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
#include "utility.h"

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
    m->xDir = 1;
    m->zDir = 1;
    m->isFalling = 1;
    m->timeTracker = 0.0;
    m->velocity = 0.0;

    return m;
}

void initMeteor(Meteor *m)
{
    // calculate landing position on flat ground where meteor should hit
    // this position does not account for generated structures in the world
    m->xLand = (rand() % (WORLDX - (2 * METEOR_EDGE_BUFFER) - 1)) + METEOR_EDGE_BUFFER;
    m->yLand = GROUND_DEPTH;
    m->zLand = (rand() % (WORLDX - (2 * METEOR_EDGE_BUFFER) - 1)) + METEOR_EDGE_BUFFER;

    // randomize the direction the starting block is
    if (rand() % 2)
    {
        m->xDir *= -1;
    }
    if (rand() % 2)
    {
        m->zDir *= -1;
    }

    // calcualte starting position by counting backwards from start
    m->x = m->xLand;
    m->y = METEOR_STARTING_Y;
    m->z = m->zLand;
    for (int i = m->yLand; i < METEOR_STARTING_Y; i++)
    {
        m->x -= m->xDir;
        m->z -= m->zDir;
    }

    m->isFalling = 1;
    m->velocity = floatRand(MIN_METEOR_SPEED, MAX_METEOR_SPEED);
}

void moveMeteor(Meteor *m)
{
    if (m->isFalling)
    {
        removeMeteor(m);

        m->x += m->xDir;
        m->y -= 1;
        m->z += m->zDir;

        checkMeteorCollision(m);
        generateMeteor(m);
    }
}

void checkMeteorCollision(Meteor *m)
{
    //! @todo check if collison is with another meteor in the air
    // get next position
    int xNext = m->x + m->xDir;
    int yNext = m->y - 1;
    int zNext = m->z + m->zDir;

    // check if the meteor is in the generated world yet
    if (isInWorld(xNext, yNext, zNext))
    {
        if (yNext == CLOUD_LEVEL)
        {
            return;
        }
        if (world[xNext][yNext][zNext] != 0)
        {
            m->isFalling = 0;
        }
    }
}

void generateMeteor(Meteor *m)
{
    int meteorColours[4] = {METEOR, RED, ORANGE, YELLOW};

    for (int i = 0; i < 4; i++)
    {
        int x = m->x - (m->xDir * i);
        int y = m->y + i;
        int z = m->z - (m->zDir * i);

        // the meteor is not falling, only draw main body with no tail
        if (i > 0 && !m->isFalling)
        {
            break;
        }

        if (isInWorld(x, y, z))
        {
            world[x][y][z] = getColour(meteorColours[i]);
        }
    }
}

void removeMeteor(Meteor *m)
{

    for (int i = 0; i < 4; i++)
    {
        int x = m->x - (m->xDir * i);
        int y = m->y + i;
        int z = m->z - (m->zDir * i);

        if (isInWorld(x, y, z))
        {
            world[x][y][z] = 0;
        }
    }
}
