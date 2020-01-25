/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef __MSANSOME_UTILITY__
#define __MSANSOME_UTILITY__

typedef enum colours
{
    INVALID_COLOUR = 0,
    EMPTY,
    GREEN,
    BROWN,
    WHITE
} Colours;

/*
* createUserColours
* Creates a list of user defined colours
*/
extern void createUserColours();

/*
* drawCircle
* Draws a circle
*/
extern void drawCircle(int xCentre, int y, int zCentre, int r, Colours colour);

/*
* getColour
* Returns a random colour of type colour
*/
extern int getColour(Colours colour);

#endif //__MSANSOME_UTILITY__