/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_generation_h
#define msansome_generation_h

#include "linkedList.h"

/**
 * Initalize the game world
 * Generate a test world to debug the graphics engine
 */
extern void createTestWorld();

/**
 * Initalize the game world
 * Generate the games main world environment
 */
extern void createMainWorld();

/**
 * Checks if the square defined by (x1,z1) (x2,z2) collides
 * with any other structure in g_structures
 * @param x1 position of starting x
 * @param z1 position of starting z
 * @param x2 position of ending x
 * @param z2 position of ending z
 * @return 1 = collision, 0 = no collision
 */
extern int checkStructureCollision(int x1, int z1, int x2, int z2);

/**
 * Gets the (x1,z1) (x2,z2) of an item
 * @param x1 position of starting x, updated with item value
 * @param z1 position of starting z, updated with item value
 * @param x2 position of ending x, updated with item value
 * @param z2 position of ending z, updated with item value
 * @return 1 = ERROR, 0 = success
 */
extern int getStructureSquare(Item *s, int *x1, int *z1, int *x2, int *z2);

#endif //msansome_generation_h