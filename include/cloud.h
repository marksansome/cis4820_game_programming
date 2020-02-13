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
    int xCenter;
    int yCenter;
    int zCenter;
    int radius;
} Cloud;

extern Cloud *createCloud();

extern void initializeCloud(Cloud *);

extern void generateCloud(Cloud *);

extern void removeCloud(Cloud *);

extern void moveCloud(Cloud *c);

extern void freeCloud(Cloud *);

#endif //msansome_cloud_h
