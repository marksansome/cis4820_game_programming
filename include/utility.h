/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_utility_h
#define msansome_utility_h

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
    RED_TEAM,
    BLUE_TEAM
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
 * Generates a random floating point number between min and max
 * @param min minimum number produced
 * @param max maximum number produced
 * @return random number between min and max
 */
extern float floatRand(float min, float max);

#endif // msansome_utility_h
