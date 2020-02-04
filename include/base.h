/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef __MSANSOME_BASE__
#define __MSANSOME_BASE__

#include "config.h"

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

extern Base *createBase();

extern void initializeBase(Base *, int, int);

extern void generateBase(Base *);

extern void freeBase(Base *);

#endif //__MSANSOME_BASE__