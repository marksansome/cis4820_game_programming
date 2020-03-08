/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "base.h"
#include "config.h"
#include "data.h"
#include "graphics.h"
#include "hill.h"
#include "linkedList.h"
#include "utility.h"
#include "valley.h"
#include "vehicle.h"

void createUserColours()
{
    // testWorld changing colour
    setUserColour(9, 0.70, 0.30, 0.70, 1.00, 0.30, 0.15, 0.30, 1.00);
    // dark green (grass)
    setUserColour(10, 0.00, 0.38, 0.00, 1.00, 0.00, 0.19, 0.00, 1.00);
    setUserColour(11, 0.00, 0.40, 0.00, 1.00, 0.00, 0.20, 0.00, 1.00);
    setUserColour(12, 0.00, 0.42, 0.00, 1.00, 0.00, 0.21, 0.00, 1.00);
    setUserColour(13, 0.00, 0.44, 0.00, 1.00, 0.00, 0.22, 0.00, 1.00);
    // dark brown (dirt)
    setUserColour(14, 0.38, 0.20, 0.00, 1.00, 0.19, 0.10, 0.00, 1.00);
    setUserColour(15, 0.40, 0.22, 0.00, 1.00, 0.20, 0.11, 0.00, 1.00);
    setUserColour(16, 0.42, 0.24, 0.00, 1.00, 0.21, 0.12, 0.00, 1.00);
    setUserColour(17, 0.44, 0.26, 0.00, 1.00, 0.22, 0.13, 0.00, 1.00);
    // white (cloud)
    setUserColour(18, 0.94, 0.94, 0.94, 1.00, 0.47, 0.47, 0.47, 0.50);
    setUserColour(19, 0.96, 0.96, 0.96, 1.00, 0.48, 0.48, 0.48, 0.50);
    setUserColour(20, 0.98, 0.98, 0.98, 1.00, 0.49, 0.49, 0.49, 0.50);
    setUserColour(21, 1.00, 1.00, 1.00, 1.00, 0.50, 0.50, 0.50, 0.50);
    // red (meteor tail)
    setUserColour(22, 1.00, 0.00, 0.00, 0.50, 0.50, 0.00, 0.00, 0.50);
    setUserColour(23, 0.69, 0.14, 0.14, 0.50, 0.43, 0.07, 0.07, 0.50);
    setUserColour(24, 0.55, 0.10, 0.10, 0.50, 0.27, 0.05, 0.05, 0.50);
    setUserColour(25, 0.50, 0.07, 0.07, 0.50, 0.25, 0.03, 0.03, 0.50);
    // yellow (meteor tail)
    setUserColour(26, 1.00, 1.00, 0.00, 0.50, 0.50, 0.50, 0.00, 0.50);
    setUserColour(27, 1.00, 0.88, 0.00, 0.50, 0.50, 0.44, 0.00, 0.50);
    setUserColour(28, 1.00, 0.80, 0.00, 0.50, 0.50, 0.40, 0.00, 0.50);
    setUserColour(29, 1.00, 0.72, 0.00, 0.50, 0.50, 0.36, 0.00, 0.50);
    // orange (meteor tail)
    setUserColour(30, 1.00, 0.27, 0.00, 0.50, 0.50, 0.14, 0.00, 0.50);
    setUserColour(31, 1.00, 0.45, 0.00, 0.50, 0.50, 0.22, 0.00, 0.50);
    setUserColour(32, 1.00, 0.55, 0.00, 0.50, 0.50, 0.26, 0.00, 0.50);
    setUserColour(33, 1.00, 0.64, 0.00, 0.50, 0.50, 0.31, 0.00, 0.50);
    // dark grey (meteor)
    setUserColour(34, 0.05, 0.16, 0.16, 1.00, 0.02, 0.09, 0.09, 1.00);
    // red (team)
    setUserColour(35, 0.70, 0.15, 0.15, 1.00, 0.35, 0.07, 0.07, 1.00);
    // blue (team)
    setUserColour(36, 0.15, 0.15, 0.70, 1.00, 0.07, 0.07, 0.35, 1.00);
    // black (vehicle tire)
    setUserColour(37, 0.01, 0.01, 0.01, 1.00, 0.00, 0.00, 0.00, 1.00);
}

void drawCircle(int xCenter, int y, int zCenter, int r, Colours colour)
{
    for (int z = -r; z < r; z++)
    {
        for (int x = -r; x < r; x++)
        {
            if (x * x + z * z < r * r)
            {
                if (isInWorld(xCenter + x, y, zCenter + z))
                {
                    world[xCenter + x][y][zCenter + z] = getColour(colour);
                }
                else
                {
                    int newX = xCenter + x;
                    int newZ = zCenter + z;
                    if ((xCenter + x) > WORLDX - 1)
                    {
                        newX -= WORLDX;
                    }
                    if ((zCenter + x) > WORLDZ - 1)
                    {
                        newZ -= WORLDZ;
                    }

                    world[newX][y][newZ] = getColour(colour);
                }
            }
        }
    }
}

int getColour(Colours colour)
{
    int greens[4] = {10, 11, 12, 13};
    int browns[4] = {14, 15, 16, 17};
    int whites[4] = {18, 19, 20, 21};
    int yellows[4] = {26, 27, 28, 29};
    int oranges[4] = {30, 31, 32, 33};
    int reds[4] = {22, 23, 24, 25};

    switch (colour)
    {
    case EMPTY:
        return 0;
    case GREEN:
        return greens[rand() % 4];
    case BROWN:
        return browns[rand() % 4];
    case WHITE:
        return whites[rand() % 4];
    case DARK_GRAY:
        return 34;
    case YELLOW:
        return yellows[rand() % 4];
    case ORANGE:
        return oranges[rand() % 4];
    case RED:
        return reds[rand() % 4];
    case RED_TEAM_COLOUR:
        return 35;
    case BLUE_TEAM_COLOUR:
        return 36;
    case VEHICLE_TIRE_COLOUR:
        return 37;
    default:
        printf("WARNING: Colour not found\n");
        return 0;
    }
}

double toDegrees(float radians)
{
    return radians * (180.0 / M_PI);
}

double toRadians(float degree)
{
    return degree / 180.0 * M_PI;
}

int isInWorld(int x, int y, int z)
{
    if (x >= WORLDX || x < 0 ||
        z >= WORLDZ || z < 0 ||
        y >= WORLDY || y < 0)
    {
        return 0;
    }
    return 1;
}

int intRand(int min, int max)
{
    float scale = rand() / (float)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);       // [min, max]
}

float floatRand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);       // [min, max]
}

int getTopPosition(int x1, int z1, int x2, int z2)
{
    int topY = -1;

    for (int x = x1; x < x2; x++)
    {
        for (int z = z1; z < z2; z++)
        {
            // for (int y = CLOUD_LEVEL - 1; y > 0; y--)
            for (int y = 0; y < (CLOUD_LEVEL - 1); y++)
            {
                if (world[x][y][z] == 0 && world[x][y + 1][z] == 0)
                {
                    if (y > topY)
                    {
                        topY = y;
                    }
                    break;
                }
            }
        }
    }

    return topY;
}

int checkCollision(List *l, int index, int x1, int z1, int x2, int z2)
{
    int isCollision = 0;
    for (int i = 0; i < getListSize(l); i++)
    {
        Item *s = getItemAtIndex(l, i);
        if (isCollision)
        {
            break;
        }

        // get next structures (x1, z1) (x2, z2)
        int x1b, z1b, x2b, z2b = 0;
        getItemSquare(s, &x1b, &z1b, &x2b, &z2b);

        if (x1 <= x2b && x2 >= x1b && z1 >= z2b && z2 <= z1b)
        {
            isCollision = 1;
        }

        // ignore collision if its with itself
        if (index == i)
        {
            isCollision = 0;
        }
    }

    return isCollision;
}

void getItemSquare(Item *s, int *x1, int *z1, int *x2, int *z2)
{
    if (s == NULL)
    {
        printf("ERROR: Trying to access NULL item\n");
        exit(1);
    }

    switch (s->type)
    {
    case VALLEY:
    {
        Valley *v = s->ptr;
        *x1 = v->x1;
        *z1 = v->z1;
        *x2 = v->x2;
        *z2 = v->z2;
        break;
    }
    case HILL:
    {
        Hill *h = s->ptr;
        *x1 = h->x1;
        *z1 = h->z1;
        *x2 = h->x2;
        *z2 = h->z2;
        break;
    }
    case BASE:
    {
        Base *b = s->ptr;
        *x1 = b->x1;
        *z1 = b->z1;
        *x2 = b->x2;
        *z2 = b->z2;
        break;
    }
    case VEHICLE:
    {
        Vehicle *v = s->ptr;
        *x1 = v->x1;
        *z1 = v->z1;
        *x2 = v->x2;
        *z2 = v->z2;
        break;
    }
    default:
    {
        printf("ERROR: Invalid ID when checking item square\n");
        exit(1);
    }
    }
}

void globalVehicleCheckProjectile(int xHit, int yHit, int zHit)
{
    // red team
    for (int i = 0; i < getListSize(g_red_team->vehicles); i++)
    {
        Vehicle *v = getItemAtIndex(g_red_team->vehicles, i)->ptr;
        for (int y = v->y; y < v->y + v->height; y++)
        {
            for (int x = v->x1; x < v->x2; x++)
            {
                for (int z = v->z1; z < v->z2; z++)
                {
                    if (x == xHit && y == yHit && z == zHit)
                    {
                        v->health -= 1;
                    }
                }
            }
        }
    }

    // blue team
    for (int i = 0; i < getListSize(g_blue_team->vehicles); i++)
    {
        Vehicle *v = getItemAtIndex(g_blue_team->vehicles, i)->ptr;
        for (int y = v->y; y < v->y + v->height; y++)
        {
            for (int x = v->x1; x < v->x2; x++)
            {
                for (int z = v->z1; z < v->z2; z++)
                {
                    if (x == xHit && y == yHit && z == zHit)
                    {
                        v->health -= 1;
                    }
                }
            }
        }
    }
}
