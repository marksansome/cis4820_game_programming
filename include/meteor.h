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
    double timeTracker;         // keep track of the last time meteor moved
    double velocity;            // time between movement, in milliseconds
} Meteor;

/**
 * Allocates memory for a Meteor
 * @return pointer to allocated Meteor
 */
extern Meteor *createMeteor();

/**
 * Initalizes a Meteor with starting values
 * @param meteor pointer to Meteor to be initalized
 */
extern void initializeMeteor(Meteor *meteor);

/**
 * Moves a meteor to the next space
 * @param meteor meteor to be moved
 */
void moveMeteor(Meteor *meteor);

/**
 * Checks that the meteor can move to the next block
 * If it cannot move, update isFalling to show that it will no longer move
 * @param meteor meteor to check
 */
void checkMeteorCollision(Meteor *meteor);

/**
 * Generates a meteor in the world
 * @param meteor meteor to be generated
 * @param withTail would you like to generate the meteor with fire tail
 * @param colour colour to generate the meteor block, 0 = remove
 */
void generateMeteor(Meteor *meteor);

/**
 * Removes a meteor from the world
 * @param meteor meteor to be un-generated
 */
void removeMeteor(Meteor *meteor);

#endif //msansome_meteor_h