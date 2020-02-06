/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
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

extern Hill *createHill();

extern void initializeHill(Hill *);

extern void generateHill(Hill *);

extern void freeHill(Hill *);

#endif //msansome_hill_h
