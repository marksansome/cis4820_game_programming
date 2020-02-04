/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef __MSANSOME_PROJECTILE__
#define __MSANSOME_PROJECTILE__

#include "config.h"

#include "projectile.h"

typedef struct projectile
{
    int mobId;
    float x;
    float y;
    float z;
    float yRot;
} Projectile;

extern Projectile *createProjectile();

#endif // __MSANSOME_PROJECTILE__
