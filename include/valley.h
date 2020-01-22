#ifndef __MSANSOME_VALLEY__
#define __MSANSOME_VALLEY__

#define MIN_VALLEY_DEPTH 2
#define MAX_VALLEY_DEPTH 3
#define MIN_VALLEY_RADIUS 6
#define MAX_VALLEY_RADIUS 12

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

#endif //__MSANSOME_VALLEY__