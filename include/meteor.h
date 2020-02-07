/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_meteor_h
#define msansome_meteor_h

typedef struct meteor
{
    int x, y, z;                // current
    int xLand, yLand, zLand;    // landing position
    int xStart, yStart, zStart; // starting position
    int xDir, zDir;             // movement directions
    int isFalling;              // has the meteor collided with the ground
} Meteor;

/**
 * Allocates memory and initalizes a meteor
 * @return new meteor
 */
extern Meteor *createMeteor();

/**
 * Initalizes a meteor with starting values
 * @param m meteor to be initalized
 */
extern void initMeteor(Meteor *m);

#endif //msansome_meteor_h