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
    WHITE
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

#endif //__MSANSOME_UTILITY__