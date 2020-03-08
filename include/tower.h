/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_tower_h
#define msansome_tower_h

#include "projectile.h"
#include "utility.h"

typedef struct tower
{
    int colour;
    int height;
    Projectile *projectile; // projectile for tower to fire
    int y;
    int x1;
    int z1;
    int x2;
    int z2;
} Tower;

/**
 * Allocates memory for a Tower struct
 * @return pointer to allocated Tower
 */
extern Tower *createTower();

/**
 * Initializes values in a Tower
 * @param tower pointer to allocated Tower
 * @param colour colour to draw Tower
 * @param position the x position of the Tower
 */
extern void initializeTower(Tower *tower, int colour, int position);

/**
 * Update a towers projectile
 * @param tower pointer to allocated Tower
 * @param vehicleTargets list of vehicles to use as projectile targets
 */
extern void updateTowerProjectile(Tower *tower, List *vehicleTargets);

/**
 * Draws Tower in the world array
 * @param tower pointer to allocated Tower
 */
extern void generateTower(Tower *tower);

/**
 * Frees the memory for a Tower
 * @param tower pointer to allocated Tower
 */
extern void freeTower(Tower *tower);

#endif //msansome_tower_h
