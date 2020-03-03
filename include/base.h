/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_base_h
#define msansome_base_h

#include "utility.h"

typedef struct base
{
    int colour;
    int height;
    int x1;
    int y1;
    int z1;
    int x2;
    int y2;
    int z2;
} Base;

/**
 * Allocates memory for a Base struct
 * @return pointer to allocated Base
 */
extern Base *createBase();

/**
 * Initializes values in a Base
 * @param base pointer to allocated Base
 * @param colour colour to draw Base
 * @param position the x position of the Base center
 */
extern void initializeBase(Base *base, int colour, int position);

/**
 * Draws Base in the world array
 * @param base pointer to allocated Base
 */
extern void generateBase(Base *base);

/**
 * Frees the memory for a Base
 * @param base pointer to allocated Base
 */
extern void freeBase(Base *base);

#endif //msansome_base_h