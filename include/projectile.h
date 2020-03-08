/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_projectile_h
#define msansome_projectile_h

typedef struct projectile
{
    int mobId;              // the mob id used to for graphics functions
    int inMotion;           // is the projectile in motion
    float x, y, z;          // current position
    float xRot, yRot, zRot; // projectiles rotation around each axis
    float xDir, yDir, zDir; // movement vector
    double timeTracker;     // keep track of the last time meteor moved
    double velocity;        // time between movement, in milliseconds
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
 * Sets projectile position
 * @param projectile projectile to update
 * @param x coordinate of position
 * @param y coordinate of position
 * @param z coordinate of position
 */
extern void setProjectilePosition(Projectile *p, float x, float y, float z);

/**
 * Sets projectile to target
 * @param projectile projectile to update
 * @param x coordinate of target
 * @param y coordinate of target
 * @param z coordinate of target
 */
extern void setProjectileTarget(Projectile *p, int x, int y, int z);

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
