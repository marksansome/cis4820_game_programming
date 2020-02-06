/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
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

extern Valley *createValley();

extern void initializeValley(Valley *);

extern void generateValley(Valley *);

extern void freeValley(Valley *v);

#endif //msansome_valley_h