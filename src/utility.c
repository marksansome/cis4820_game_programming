/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"
#include "config.h"
#include "graphics.h"

void createUserColours()
{
    // testWorld changing colour
    setUserColour(9, 0.7, 0.3, 0.7, 1.0, 0.3, 0.15, 0.3, 1.0);
    // dark green (grass)
    setUserColour(10, 0.0, 0.38, 0.0, 1.0, 0.0, 0.19, 0.0, 1.0);
    setUserColour(11, 0.0, 0.40, 0.0, 1.0, 0.0, 0.20, 0.0, 1.0);
    setUserColour(12, 0.0, 0.42, 0.0, 1.0, 0.0, 0.21, 0.0, 1.0);
    setUserColour(13, 0.0, 0.44, 0.0, 1.0, 0.0, 0.22, 0.0, 1.0);
    // dark brown (dirt)
    setUserColour(14, 0.38, 0.20, 0.0, 1.0, 0.19, 0.10, 0.0, 1.0);
    setUserColour(15, 0.40, 0.22, 0.0, 1.0, 0.20, 0.11, 0.0, 1.0);
    setUserColour(16, 0.42, 0.24, 0.0, 1.0, 0.21, 0.12, 0.0, 1.0);
    setUserColour(17, 0.44, 0.26, 0.0, 1.0, 0.22, 0.13, 0.0, 1.0);
    // white (cloud)
    setUserColour(18, 0.62, 0.62, 0.62, 0.5, 0.31, 0.31, 0.31, 0.5);
    setUserColour(19, 0.75, 0.75, 0.75, 0.5, 0.37, 0.37, 0.37, 0.5);
    setUserColour(20, 0.87, 0.87, 0.87, 0.5, 0.43, 0.43, 0.43, 0.5);
    setUserColour(21, 1.00, 1.00, 1.00, 0.5, 0.50, 0.50, 0.50, 0.5);
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
    default:
        printf("WARNING: random colour not found\n");
        return 0;
    }
}
