#ifndef __MSANSOME_VALLEY__
#define __MSANSOME_VALLEY__

#define NUM_VALLEYS 10
#define VALLEY_DEPTH 3
#define MIN_VALLEY_RADIUS 5
#define MAX_VALLEY_RADIUS 10

typedef struct valley
{
    int radius;
    int x;
    int z;
} Valley;

extern Valley *createValley();
extern void initializeValley(Valley *);
extern void generateValley(Valley *);
extern void freeValley(Valley *v);

#endif //__MSANSOME_VALLEY__