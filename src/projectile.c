/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "projectile.h"
#include "generation.h"

Projectile *createProjectile()
{
    Projectile *p = (Projectile *)malloc(sizeof(Projectile));
    if (p == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    p->mobId = -1;
    p->x = 0.0;
    p->y = 0.0;
    p->z = 0.0;
    p->yRot = 0.0;

    return p;
}