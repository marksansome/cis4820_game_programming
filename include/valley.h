#ifndef __MSANSOME_VALLEY__
#define __MSANSOME_VALLEY__

#define NUM_VALLEYS 10
#define VALLEY_DEPTH 3
#define MIN_VALLEY_RADIUS 5
#define MAX_VALLEY_RADIUS 15

typedef struct valley
{
    int radius;
    int x;
    int z;
} Valley;

void initializeValley(Valley *);
void generateValley(Valley);

#endif //__MSANSOME_VALLEY__