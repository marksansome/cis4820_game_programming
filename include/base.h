#ifndef __MSANSOME_BASE__
#define __MSANSOME_BASE__

// y
#define BASE_HEIGHT 3
// x
#define BASE_LENGTH 5
// z
#define BASE_WIDTH 5

typedef struct base
{
    int colour;
    int length;
    int width;
    int height;
    int x;
    int y;
    int z;
} Base;

extern Base *createBase();
extern void initializeBase(Base *, int, int);
extern void generateBase(Base *);
extern void freeBase(Base *);

#endif //__MSANSOME_BASE__