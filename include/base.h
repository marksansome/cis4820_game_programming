#ifndef __MSANSOME_BASE__
#define __MSANSOME_BASE__

#define BASE_HEIGHT 3
#define BASE_EDGE_LENGTH 5

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