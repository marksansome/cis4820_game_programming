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

/**
 * Allocates memory for a Cloud struct
 * @return pointer to allocated Cloud
 */
extern Cloud *createCloud();

/**
 * Initializes values in a Cloud
 * @param cloud pointer to allocated Cloud
 */
extern void initializeCloud(Cloud *cloud);

/**
 * Draws Cloud in the world array
 * @param cloud pointer to allocated Cloud
 */
extern void generateCloud(Cloud *cloud);

/**
 * Redraws Cloud in the world array with colour 0 (empty)
 * @param cloud pointer to allocated Cloud
 */
extern void removeCloud(Cloud *cloud);

/**
 * Moves Cloud by incrementing stored values and regenerating
 * @param cloud pointer to allocated Cloud
 */
extern void moveCloud(Cloud *cloud);

/**
 * Frees the memory for a Cloud
 * @param cloud pointer to allocated Cloud
 */
extern void freeCloud(Cloud *cloud);

#endif //msansome_cloud_h
