#ifndef __MSANSOME_HILL__
#define __MSANSOME_HILL__

#define MIN_HILL_HEIGHT 2
#define MAX_HILL_HEIGHT 3
#define MIN_HILL_RADIUS 6
#define MAX_HILL_RADIUS 12
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

#endif //__MSANSOME_HILL__
