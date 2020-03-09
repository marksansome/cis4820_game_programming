/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "graphics.h"
#include "projectile.h"
#include "tower.h"
#include "utility.h"
#include "vehicle.h"

Tower *createTower()
{
    Tower *t = (Tower *)malloc(sizeof(Tower));
    if (t == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    t->colour = 0;
    t->height = 0;
    t->x1 = 0;
    t->z1 = 0;
    t->x2 = 0;
    t->z2 = 0;
    t->y = 0;

    return t;
}

void initializeTower(Tower *t, int colour, int towerPos)
{
    //! @todo: try to make sure these don't spawn next to each other

    t->colour = colour;
    t->height = TOWER_HEIGHT;

    // t->x1 = towerPos;
    t->x1 = intRand((WORLDX - (2 * TOWER_EDGE_LENGTH) - 1), TOWER_EDGE_LENGTH);
    t->z1 = intRand((WORLDZ - (2 * TOWER_EDGE_LENGTH) - 1), TOWER_EDGE_LENGTH);
    t->x2 = t->x1 + TOWER_EDGE_LENGTH;
    t->z2 = t->z1 + TOWER_EDGE_LENGTH;
    t->y = getTopPosition(t->x1, t->z1, t->x2, t->z2);

    t->projectile = createProjectile();
    t->projectile->velocity *= TOWER_PROJ_SPEED_MULT;
    setProjectilePosition(t->projectile, (float)t->x1 + ((float)TOWER_EDGE_LENGTH / 4.0), (float)(t->y + t->height) + 0.5, (float)t->z1 + ((float)TOWER_EDGE_LENGTH / 4.0));
}

void updateTowerProjectile(Tower *t, List *vehicleTargets)
{
    // if not in motion, find new target
    if (!t->projectile->inMotion)
    {
        setProjectilePosition(t->projectile, (float)t->x1 + ((float)TOWER_EDGE_LENGTH / 4.0), (float)(t->y + t->height) + 0.5, (float)t->z1 + ((float)TOWER_EDGE_LENGTH / 4.0));
        for (int i = 0; i < getListSize(vehicleTargets); i++)
        {
            Vehicle *v = getItemAtIndex(vehicleTargets, i)->ptr;
            if ((abs(v->x1 - t->x1) <= TOWER_SEARCH_RADIUS) &&
                (abs(v->z1 - t->z1) <= TOWER_SEARCH_RADIUS))
            {
                // vehicle in range, target
                setProjectileTarget(t->projectile, v->x1 + 1, v->y + (v->height / 2), v->z1 + 1);
                fireProjectile(t->projectile);
                break;
            }
        }
    }
    // move projectile
    moveProjectile(t->projectile);
}

void generateTower(Tower *t)
{
    // draw square size of base edge
    for (int y = t->y; y < t->y + t->height; y++)
    {
        for (int x = t->x1; x < t->x2; x++)
        {
            for (int z = t->z1; z < t->z2; z++)
            {
                world[x][y][z] = t->colour;
            }
        }
    }

    showMob(t->projectile->mobId);

    // debug show square (x1,z1) (x2,z2)
    // world[b->x1][b->y1][b->z1] = 7;
    // world[b->x2][b->y2][b->z2] = 8;
}

void removeTower(Tower *t)
{
    // draw square size of base edge
    for (int y = t->y; y < t->y + t->height; y++)
    {
        for (int x = t->x1; x < t->x2; x++)
        {
            for (int z = t->z1; z < t->z2; z++)
            {
                world[x][y][z] = getColour(EMPTY);
            }
        }
    }

    hideMob(t->projectile->mobId);

    // debug show square (x1,z1) (x2,z2)
    // world[b->x1][b->y1][b->z1] = 7;
    // world[b->x2][b->y2][b->z2] = 8;
}

void freeTower(Tower *t)
{
    free(t);
}
