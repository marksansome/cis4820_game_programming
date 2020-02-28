/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_data_h
#define msansome_data_h

#include "linkedList.h"
#include "projectile.h"

/**
 * List to store structures (Base, Hill, Valley)
 * for generating the world at game start
 */
extern List *g_structures;

/**
 * List to store Clouds and keep track of their position
 */
extern List *g_clouds;

/**
 * List to store Meteors and keep track of their position
 */
extern List *g_meteors;

/**
 * Storage for the user projectile and position
 */
extern Projectile *g_projectile;

/**
 * Tracking of the total number of mobs created in the world
 * Used to indicate how many more mobs can be created
 */
extern int g_num_mobs;

/**
 * Set the world array to 0
 */
extern void initializeWorld();

#endif //msansome_data_h