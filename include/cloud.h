/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_cloud_h
#define msansome_cloud_h

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

#endif //msansome_cloud_h