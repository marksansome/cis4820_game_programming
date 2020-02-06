/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef msansome_projectile_h
#define msansome_projectile_h

typedef struct projectile
{
    int mobId;
    int inMotion;
    float x;
    float y;
    float z;
    float xRot;
    float yRot;
    float zRot;
} Projectile;

extern Projectile *g_projectile;

extern void initProjectile();

extern void fireProjectile();

extern void moveProjectile();

extern void checkProjectileCollision();

extern double toRadians(float degrees);

#endif //msansome_projectile_h
