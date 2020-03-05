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

void setProjectileToViewPosition(Projectile *p)
{
    // get players position for starting point
    getViewPosition(&p->x, &p->y, &p->z);
    getViewOrientation(&p->xRot, &p->yRot, &p->zRot);
    p->x *= -1.0;
    p->y *= -1.0;
    p->z *= -1.0;
    p->x -= 0.5;
    p->y -= 0.5;
    p->z -= 0.5;
}

void fireProjectile(Projectile *p)
{
    if (!p->inMotion)
    {
        setMobPosition(p->mobId, p->x, p->y, p->z, p->zRot);
        showMob(p->mobId);
        p->inMotion = 1;
    }
}

void moveProjectile(Projectile *p)
{
    if (p->inMotion)
    {
        float unitMultiplier = 1.0 - fabs(pow(sin(toRadians(p->xRot)), 3));

        p->x += (sin(toRadians(p->yRot)) * cos(toRadians(p->xRot)) * unitMultiplier);
        p->y -= (sin(toRadians(p->xRot)));
        p->z -= (cos(toRadians(p->yRot)) * cos(toRadians(p->xRot)) * unitMultiplier);

        checkProjectileCollision(p);
        // calculate new position
        if (p->inMotion)
        {
            setMobPosition(p->mobId, p->x, p->y, p->z, -p->yRot + 180.0);
        }
    }
}

void checkProjectileCollision(Projectile *p)
{
    int isCollision = 0;

    for (float i = p->x - 0.1; i < p->x + (0.5 * 2.0); i += 0.1)
    {
        for (float j = p->z - 0.1; j < p->z + (0.5 * 2.0); j += 0.1)
        {
            for (float k = p->y - 0.1; k < p->y + (0.5 * 2.0); k += 0.1)
            {
                if (world[(int)i][(int)k][(int)j] != 0)
                {
                    hideMob(p->mobId);
                    p->inMotion = 0;
                    if (!isCollision)
                    {
                        world[(int)i][(int)k][(int)j] = 0;
                        globalVehicleCheckProjectile(i, k, j);
                        isCollision = 1;
                    }
                }
            }
        }
    }

    if (p->x >= (WORLDX - 1.15) || p->x <= 0.15 ||
        p->z >= (WORLDZ - 1.15) || p->z <= 0.15 ||
        p->y >= (WORLDY - WORLD_CLOUD_GAP - 0.15) || p->y <= 0.15)
    {
        hideMob(p->mobId);
        p->inMotion = 0;
    }
}
