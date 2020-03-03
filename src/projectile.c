/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "projectile.h"

#include "data.h"
#include "graphics.h"
#include "utility.h"

// Projectile *g_player_projectile;

Projectile *createProjectile()
{
    Projectile *p = (Projectile *)malloc(sizeof(Projectile));
    if (p == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    // add projectile mob to global mob counter
    int id = g_num_mobs;
    g_num_mobs += 1; // add to mob counter

    createMob(id, 0.0, 0.0, 0.0, 0.0);
    hideMob(id);

    p->mobId = id;
    p->inMotion = 0;
    p->x = 0.0;
    p->y = 0.0;
    p->z = 0.0;
    p->xRot = 0.0;
    p->yRot = 0.0;
    p->zRot = 0.0;

    return p;
}

void fireProjectile()
{
    if (!g_player_projectile->inMotion)
    {
        // get players position for starting point
        getViewPosition(&g_player_projectile->x, &g_player_projectile->y, &g_player_projectile->z);
        getViewOrientation(&g_player_projectile->xRot, &g_player_projectile->yRot, &g_player_projectile->zRot);

        g_player_projectile->x *= -1.0;
        g_player_projectile->y *= -1.0;
        g_player_projectile->z *= -1.0;

        g_player_projectile->x -= 0.5;
        g_player_projectile->y -= 0.5;
        g_player_projectile->z -= 0.5;

        setMobPosition(g_player_projectile->mobId, g_player_projectile->x, g_player_projectile->y, g_player_projectile->z, g_player_projectile->zRot);
        showMob(g_player_projectile->mobId);
        g_player_projectile->inMotion = 1;
    }
}

void moveProjectile()
{
    if (g_player_projectile->inMotion)
    {
        float unitMultiplier = 1.0 - fabs(pow(sin(toRadians(g_player_projectile->xRot)), 3));

        g_player_projectile->x += (sin(toRadians(g_player_projectile->yRot)) * cos(toRadians(g_player_projectile->xRot)) * unitMultiplier);
        g_player_projectile->y -= (sin(toRadians(g_player_projectile->xRot)));
        g_player_projectile->z -= (cos(toRadians(g_player_projectile->yRot)) * cos(toRadians(g_player_projectile->xRot)) * unitMultiplier);

        checkProjectileCollision();
        // calculate new position
        if (g_player_projectile->inMotion)
        {
            setMobPosition(g_player_projectile->mobId, g_player_projectile->x, g_player_projectile->y, g_player_projectile->z, -g_player_projectile->yRot + 180.0);
        }
    }
}

void checkProjectileCollision()
{
    int isCollision = 0;

    for (float i = g_player_projectile->x - 0.1; i < g_player_projectile->x + (0.5 * 2.0); i += 0.1)
    {
        for (float j = g_player_projectile->z - 0.1; j < g_player_projectile->z + (0.5 * 2.0); j += 0.1)
        {
            for (float k = g_player_projectile->y - 0.1; k < g_player_projectile->y + (0.5 * 2.0); k += 0.1)
            {
                if (world[(int)i][(int)k][(int)j] != 0)
                {
                    hideMob(g_player_projectile->mobId);
                    g_player_projectile->inMotion = 0;
                    if (!isCollision)
                    {
                        world[(int)i][(int)k][(int)j] = 0;
                        isCollision = 1;
                    }
                }
            }
        }
    }

    if (g_player_projectile->x >= (WORLDX - 1.15) || g_player_projectile->x <= 0.15 ||
        g_player_projectile->z >= (WORLDZ - 1.15) || g_player_projectile->z <= 0.15 ||
        g_player_projectile->y >= (WORLDY - WORLD_CLOUD_GAP - 0.15) || g_player_projectile->y <= 0.15)
    {
        hideMob(g_player_projectile->mobId);
        g_player_projectile->inMotion = 0;
    }
}
