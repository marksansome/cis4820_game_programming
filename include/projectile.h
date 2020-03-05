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
 * Sets projectile to players view point
 * @param projectile projectile to update
 */
extern void setProjectileToViewPosition(Projectile *p);

/**
 * Fire projectile from player
 * @param projectile projectile to fire
 */
extern void fireProjectile(Projectile *projectile);

/**
 * Move projectile to next position based on rotation angles
 * @param projectile projectile to move
 */
extern void moveProjectile(Projectile *projectile);

/**
 * Check if projectile has collided with something
 * @param projectile projectile to check
 */
extern void checkProjectileCollision(Projectile *projectile);

#endif //msansome_projectile_h
