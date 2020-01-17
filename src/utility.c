
#include "graphics.h"
#include "utility.h"

void createUserColours()
{
    // testWorld changing colour
    setUserColour(9, 0.7, 0.3, 0.7, 1.0, 0.3, 0.15, 0.3, 1.0);
    // dark green (grass)
    setUserColour(10, 0.0, 0.50, 0.0, 1.0, 0.0, 0.25, 0.0, 1.0);
    // dark brown (dirt)
    setUserColour(11, 0.39, 0.20, 0.0, 1.0, 0.19, 0.10, 0.0, 1.0);
}

void drawCircle(int xCentre, int y, int zCentre, int r, int colour)
{
    for (int z = -r; z < r; z++)
    {
        for (int x = -r; x < r; x++)
        {
            if (x * x + z * z < r * r)
            {
                world[xCentre + x][y][zCentre + z] = colour;
            }
        }
    }
}