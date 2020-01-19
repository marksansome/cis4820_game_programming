#ifndef __MSANSOME_HILL__
#define __MSANSOME_HILL__

#define NUM_HILLS 10
#define HILL_DEPTH 3
#define MIN_HILL_RADIUS 5
#define MAX_HILL_RADIUS 10

typedef struct hill
{
    int radius;
    int x;
    int z;
} Hill;

extern void initializeHill(Hill *);
extern void generateHill(Hill);

#endif //__MSANSOME_HILL__
