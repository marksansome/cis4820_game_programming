/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_hill_h
#define msansome_hill_h

typedef struct hill
{
    int radius;
    int height;
    int xCenter;
    int yCenter;
    int zCenter;
    int x1;
    int z1;
    int x2;
    int z2;
} Hill;

/**
 * Allocates memory for a Hill struct
 * @return pointer to allocated Hill
 */
extern Hill *createHill();

/**
 * Initializes values in a Hill
 * @param hill pointer to allocated Hill
 */
extern void initializeHill(Hill *hill);

/**
 * Draws Hill in the world array
 * @param hill pointer to allocated Hill
 */
extern void generateHill(Hill *hill);

/**
 * Frees the memory for a Hill
 * @param hill pointer to allocated Hill
 */
extern void freeHill(Hill *hill);

#endif //msansome_hill_h
