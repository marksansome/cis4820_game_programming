#ifndef __MSANSOME_HILL__
#define __MSANSOME_HILL__

#define NUM_HILLS 25
#define HILL_DEPTH 3
#define MIN_HILL_RADIUS 6
#define MAX_HILL_RADIUS 12

typedef struct hill
{
    int radius;
    int x;
    int z;
} Hill;

extern Hill *createHill();
extern void initializeHill(Hill *);
extern void generateHill(Hill *);
extern void freeHill(Hill *);

#endif //__MSANSOME_HILL__
