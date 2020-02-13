/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "utility.h"

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
    setUserColour(18, 0.62, 0.62, 0.62, 0.50, 0.31, 0.31, 0.31, 0.50);
    setUserColour(19, 0.75, 0.75, 0.75, 0.50, 0.37, 0.37, 0.37, 0.50);
    setUserColour(20, 0.87, 0.87, 0.87, 0.50, 0.43, 0.43, 0.43, 0.50);
    setUserColour(21, 1.00, 1.00, 1.00, 0.50, 0.50, 0.50, 0.50, 0.50);
    // red
    setUserColour(22, 1.00, 0.00, 0.00, 0.50, 0.50, 0.00, 0.00, 0.50);
    setUserColour(23, 0.69, 0.14, 0.14, 0.50, 0.43, 0.07, 0.07, 0.50);
    setUserColour(24, 0.55, 0.10, 0.10, 0.50, 0.27, 0.05, 0.05, 0.50);
    setUserColour(25, 0.50, 0.07, 0.07, 0.50, 0.25, 0.03, 0.03, 0.50);

    // yellow
    setUserColour(26, 1.00, 1.00, 0.00, 0.50, 0.50, 0.50, 0.00, 0.50);
    setUserColour(27, 1.00, 0.88, 0.00, 0.50, 0.50, 0.44, 0.00, 0.50);
    setUserColour(28, 1.00, 0.80, 0.00, 0.50, 0.50, 0.40, 0.00, 0.50);
    setUserColour(29, 1.00, 0.72, 0.00, 0.50, 0.50, 0.36, 0.00, 0.50);

    // orange
    setUserColour(30, 1.00, 0.27, 0.00, 0.50, 0.50, 0.14, 0.00, 0.50);
    setUserColour(31, 1.00, 0.45, 0.00, 0.50, 0.50, 0.22, 0.00, 0.50);
    setUserColour(32, 1.00, 0.55, 0.00, 0.50, 0.50, 0.26, 0.00, 0.50);
    setUserColour(33, 1.00, 0.64, 0.00, 0.50, 0.50, 0.31, 0.00, 0.50);

    // dark grey (meteor)
    setUserColour(34, 0.05, 0.16, 0.16, 1.00, 0.02, 0.09, 0.09, 1.00);

    // red (base)
    setUserColour(35, 1.00, 0.00, 0.00, 1.00, 0.50, 0.00, 0.00, 1.00);

    // blue (base)
    setUserColour(36, 0.00, 0.00, 1.00, 1.00, 0.00, 0.00, 0.50, 1.00);
}

void getUser2DColours(int colour)
{
    // switch (colour){
    //     case 9:
    //     case 10:
    //     case 11:
    //     case
    // }
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
    setUserColour(18, 0.62, 0.62, 0.62, 0.50, 0.31, 0.31, 0.31, 0.50);
    setUserColour(19, 0.75, 0.75, 0.75, 0.50, 0.37, 0.37, 0.37, 0.50);
    setUserColour(20, 0.87, 0.87, 0.87, 0.50, 0.43, 0.43, 0.43, 0.50);
    setUserColour(21, 1.00, 1.00, 1.00, 0.50, 0.50, 0.50, 0.50, 0.50);
    // red
    setUserColour(22, 1.00, 0.00, 0.00, 0.50, 0.50, 0.00, 0.00, 0.50);
    setUserColour(23, 0.69, 0.14, 0.14, 0.50, 0.43, 0.07, 0.07, 0.50);
    setUserColour(24, 0.55, 0.10, 0.10, 0.50, 0.27, 0.05, 0.05, 0.50);
    setUserColour(25, 0.50, 0.07, 0.07, 0.50, 0.25, 0.03, 0.03, 0.50);

    // yellow
    setUserColour(26, 1.00, 1.00, 0.00, 0.50, 0.50, 0.50, 0.00, 0.50);
    setUserColour(27, 1.00, 0.88, 0.00, 0.50, 0.50, 0.44, 0.00, 0.50);
    setUserColour(28, 1.00, 0.80, 0.00, 0.50, 0.50, 0.40, 0.00, 0.50);
    setUserColour(29, 1.00, 0.72, 0.00, 0.50, 0.50, 0.36, 0.00, 0.50);

    // orange
    setUserColour(30, 1.00, 0.27, 0.00, 0.50, 0.50, 0.14, 0.00, 0.50);
    setUserColour(31, 1.00, 0.45, 0.00, 0.50, 0.50, 0.22, 0.00, 0.50);
    setUserColour(32, 1.00, 0.55, 0.00, 0.50, 0.50, 0.26, 0.00, 0.50);
    setUserColour(33, 1.00, 0.64, 0.00, 0.50, 0.50, 0.31, 0.00, 0.50);

    // dark grey (meteor)
    setUserColour(34, 0.05, 0.16, 0.16, 1.00, 0.02, 0.09, 0.09, 1.00);
}

void drawCircle(int xCentre, int y, int zCentre, int r, Colours colour)
{
    for (int z = -r; z < r; z++)
    {
        for (int x = -r; x < r; x++)
        {
            if (x * x + z * z < r * r)
            {
                world[xCentre + x][y][zCentre + z] = getColour(colour);
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
    default:
        printf("WARNING: random colour not found\n");
        return 0;
    }
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

float floatRand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; // [0, 1.0]
    return min + scale * (max - min);       // [min, max]
}
