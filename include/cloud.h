#ifndef __MSANSOME_CLOUD__
#define __MSANSOME_CLOUD__

#define CLOUD_LEVEL 48

typedef struct cloud
{
    int colour;
    int x;
    int y;
    int z;
} Cloud;

extern Cloud *createCloud();
extern void initializeCloud(Cloud *);
extern void generateCloud(Cloud *);
extern int moveCloud(Cloud *c, int speed);
extern void freeCloud(Cloud *);

#endif //__MSANSOME_CLOUD__