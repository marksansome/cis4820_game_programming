/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_valley_h
#define msansome_valley_h

typedef struct valley
{
    int radius;
    int depth;
    int xCenter;
    int yCenter;
    int zCenter;
    int x1;
    int z1;
    int x2;
    int z2;
} Valley;

/**
 * Allocates memory for a Valley struct
 * @return pointer to allocated Valley
 */
extern Valley *createValley();

/**
 * Initializes values in a Valley
 * @param valley pointer to allocated Valley
 */
extern void initializeValley(Valley *valley);

/**
 * Draws Valley in the world array
 * @param valley pointer to allocated Valley
 */
extern void generateValley(Valley *valley);

/**
 * Frees the memory for a Valley
 * @param valley pointer to allocated Valley
 */
extern void freeValley(Valley *valley);

#endif //msansome_valley_h
