/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "data.h"
#include "graphics.h"
#include "linkedList.h"

List *g_structures;
List *g_clouds;
List *g_meteors;

Projectile *g_projectile;

int g_num_mobs;

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
