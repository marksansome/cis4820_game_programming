/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "projectile.h"
#include "data.h"
#include "graphics.h"

Projectile *g_projectile;

void initProjectile()
{
    g_projectile = (Projectile *)malloc(sizeof(Projectile));
    if (g_projectile == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    // add projectile mob
    int id = g_num_mobs;
    g_num_mobs += 1; // add to mob counter

    createMob(id, 0.0, 0.0, 0.0, 0.0);
    hideMob(id);

    g_projectile->mobId = id;
    g_projectile->inMotion = 0;
    g_projectile->x = 0.0;
    g_projectile->y = 0.0;
    g_projectile->z = 0.0;
    g_projectile->xRot = 0.0;
    g_projectile->yRot = 0.0;
    g_projectile->zRot = 0.0;
}

void fireProjectile()
{
    if (!g_projectile->inMotion)
    {
        // get players position for starting point
        getViewPosition(&g_projectile->x, &g_projectile->y, &g_projectile->z);
        getViewOrientation(&g_projectile->xRot, &g_projectile->yRot, &g_projectile->zRot);

        g_projectile->x *= -1.0;
        g_projectile->y *= -1.0;
        g_projectile->z *= -1.0;

        setMobPosition(g_projectile->mobId, g_projectile->x, g_projectile->y, g_projectile->z, g_projectile->zRot);
        showMob(g_projectile->mobId);
        g_projectile->inMotion = 1;
    }
}

void moveProjectile()
{
    if (g_projectile->inMotion)
    {
        float unitMultiplier = 1.0 - fabs(pow(sin(toRadians(g_projectile->xRot)), 3));

        g_projectile->x += sin(toRadians(g_projectile->yRot)) * cos(toRadians(g_projectile->xRot)) * unitMultiplier;
        g_projectile->y -= sin(toRadians(g_projectile->xRot));
        g_projectile->z -= cos(toRadians(g_projectile->yRot)) * cos(toRadians(g_projectile->xRot)) * unitMultiplier;

        checkProjectileCollision();
        // calculate new position
        if (g_projectile->inMotion)
        {
            setMobPosition(g_projectile->mobId, g_projectile->x, g_projectile->y, g_projectile->z, -g_projectile->yRot + 180.0);
        }
    }
}

void checkProjectileCollision()
{
    int isCollision = 0;

    for (float i = g_projectile->x - 0.1; i < g_projectile->x + (0.5 * 2.0); i += 0.1)
    {
        for (float j = g_projectile->z - 0.1; j < g_projectile->z + (0.5 * 2.0); j += 0.1)
        {
            for (float k = g_projectile->y - 0.1; k < g_projectile->y + (0.5 * 2.0); k += 0.1)
            {
                if (world[(int)i][(int)k][(int)j] != 0)
                {
                    hideMob(g_projectile->mobId);
                    g_projectile->inMotion = 0;
                    if (!isCollision)
                    {
                        world[(int)i][(int)k][(int)j] = 0;
                        isCollision = 1;
                    }
                }
            }
        }
    }

    if (g_projectile->x >= (WORLDX - 1.15) || g_projectile->x <= 0.15 ||
        g_projectile->z >= (WORLDZ - 1.15) || g_projectile->z <= 0.15 ||
        g_projectile->y >= (WORLDY - WORLD_CLOUD_GAP - 0.15) || g_projectile->y <= 0.15)
    {
        hideMob(g_projectile->mobId);
        g_projectile->inMotion = 0;
    }
}

double toRadians(float degree)
{
    return degree / 180.0 * M_PI;
}
