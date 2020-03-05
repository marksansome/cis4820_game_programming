/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_utility_h
#define msansome_utility_h

#include "linkedList.h"

typedef enum colours
{
    INVALID_COLOUR = 0,
    EMPTY,
    GREEN,
    BROWN,
    WHITE,
    DARK_GRAY,
    YELLOW,
    ORANGE,
    RED,
    RED_TEAM_COLOUR,
    BLUE_TEAM_COLOUR,
    VEHICLE_TIRE_COLOUR
} Colours;

/**
* Creates a set of user defined colours
*/
extern void createUserColours();

/**
* Draws a circle in the world array
* @param x x position of center
* @param y y position of center
* @param z z position of center
* @param r radius of circle
* @param colour user defined colour of the circle 
*/
extern void drawCircle(int x, int y, int z, int r, Colours colour);

/**
* Returns a random colour of type colour
* @param colour type of user defined colour
* @return integer of user defined colour
*/
extern int getColour(Colours colour);

/**
 * converts degrees to radians
 * @param degree
 * @return radians
 */
extern double toRadians(float degree);

/**
 * checks to see if coordinates are within the world array
 * @param x x position
 * @param y y position
 * @param z z position
 * @return 1 = is in world, 0 = out of world
 */
extern int isInWorld(int x, int y, int z);

/**
 * Generates a random number between min and max
 * @param min minimum number produced
 * @param max maximum number produced
 * @return random number between min and max
 */
extern int intRand(int min, int max);

/**
 * Generates a random floating point number between min and max
 * @param min minimum number produced
 * @param max maximum number produced
 * @return random number between min and max
 */
extern float floatRand(float min, float max);

/**
 * Gets the next empty y value that fits a the square specifed (x1,z1) (x2,z2)
 * @param x1 position of starting x
 * @param z1 position of starting z
 * @param x2 position of ending x
 * @param z2 position of ending z
 * @return top empty y position, -1 if no possible position
 */
extern int getTopPosition(int x1, int z1, int x2, int z2);

/**
 * Checks if the square defined by (x1,z1) (x2,z2) collides
 * with any other item in a given List
 * @param list list to check collision
 * @param index index of item being checked, use -1 if item has not be added yet
 * @param x1 position of starting x
 * @param z1 position of starting z
 * @param x2 position of ending x
 * @param z2 position of ending z
 * @return 1 = collision, 0 = no collision
 */
extern int checkCollision(List *list, int index, int x1, int z1, int x2, int z2);

/**
 * Gets the (x1,z1) (x2,z2) of an item
 * @param item item to get (x1,z1) (x2,z2)
 * @param x1 position of starting x, updated with item value
 * @param z1 position of starting z, updated with item value
 * @param x2 position of ending x, updated with item value
 * @param z2 position of ending z, updated with item value
 */
extern void getItemSquare(Item *item, int *x1, int *z1, int *x2, int *z2);

/**
 * Checks if a projectiles collision is on a vehicle, update vehicle health
 * @param x x position projectile hit
 * @param y y position projectile hit
 * @param z z position projectile hit
 */
extern void globalVehicleCheckProjectile(int x, int y, int z);

#endif // msansome_utility_h
