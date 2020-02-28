/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
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

/**
 * Allocates memory for a Projectile struct
 * @return pointer to allocated Projectile
 */
extern Projectile *createProjectile();

/**
 * Fire projectile from player
 */
extern void fireProjectile();

/**
 * Move projectile to next position based on rotation angles
 */
extern void moveProjectile();

/**
 * Check if projectile has collided with something
 */
extern void checkProjectileCollision();

#endif //msansome_projectile_h
