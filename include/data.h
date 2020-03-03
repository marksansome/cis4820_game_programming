/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_data_h
#define msansome_data_h

#include "linkedList.h"
#include "projectile.h"
#include "team.h"

/**
 * Red team data
 * store all information related to the team
 */
extern Team *g_red_team;

/**
 * Blue team data
 * store all information related to the team
 */
extern Team *g_blue_team;

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
 * List to store Meteors that have landed and keep track of their position
 */
extern List *g_meteors;

/**
 * List to store Meteors that a falling and keep track of their position
 */
extern List *g_falling_meteors;

/**
 * Storage for the user projectile and position
 */
extern Projectile *g_player_projectile;

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