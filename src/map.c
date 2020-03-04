/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "map.h"

void mapDrawViewPosition(int mapWidthOffset, int mapHeightOffset, int blockSize)
{
    GLfloat white[] = {1, 1, 1, 1};

    // get viewpoint position
    float vpX, vpY, vpZ = 0.0;
    getViewPosition(&vpX, &vpY, &vpZ);
    vpX *= -1.0;
    vpZ *= -1.0;

    // draw viewpoint
    set2Dcolour(white);
    draw2Dbox(mapWidthOffset + (blockSize * (int)vpX),
              mapHeightOffset - (blockSize * (int)vpZ),
              mapWidthOffset + (blockSize * (int)vpX) + blockSize,
              mapHeightOffset - (blockSize * (int)vpZ) + blockSize);
}

void mapDrawWorld(int mapWidthOffset, int mapHeightOffset, int blockSize)
{
    // loop through world array and draw blocks
    for (int y = WORLDY - 2; y >= 0; y--) // minus 2 to ensure we don't check out of array bounds
    {
        for (int x = 0; x < WORLDX; x++)
        {
            for (int z = 0; z < WORLDZ; z++)
            {
                if (world[x][y][z] != 0 && y != CLOUD_LEVEL) // don't draw clouds
                {
                    // to increase performace, only draw top most blocks (visable)
                    if (world[x][y + 1][z] == 0)
                    {
                        // get block colour
                        GLfloat ambRed, ambGreen, ambBlue, ambAlpha, difRed, difGreen, difBlue, difAlpha;
                        getUserColour(world[x][y][z], &ambRed, &ambGreen, &ambBlue, &ambAlpha, &difRed, &difGreen, &difBlue, &difAlpha);
                        float colour[4] = {ambRed, ambGreen, ambBlue, 1.0};

                        // draw block
                        set2Dcolour(colour);
                        draw2Dbox(mapWidthOffset + (blockSize * x),
                                  mapHeightOffset - (blockSize * z),
                                  mapWidthOffset + (blockSize * x) + blockSize,
                                  mapHeightOffset - (blockSize * z) + blockSize);
                    }
                }
            }
        }
    }
}
