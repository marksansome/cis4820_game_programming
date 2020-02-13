/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_generation_h
#define msansome_generation_h

#include "linkedList.h"

/*
* createTestWorld
* Initalize the game world
* Generate a test world to debug the graphics engine
*/
extern void createTestWorld();

/*
* createMainWorld
* Initalize the game world
* Generate the games main world environment
*/
extern void createMainWorld();

/*
* checkStructureCollision
* Checks if the square defined by (x1,z1) (x2,z2) collides with
* any other structure in gameObjects. Exclude its own index
* Out:
* 1 = collision
* 0 = no collision
*/
extern int checkStructureCollision(int index, int x1, int z1, int x2, int z2);

/*
* checkCircleStructureCollision
* Checks if the values collide with any other
* structure in gameObjects. Exclude its own index
* Out:
* 1 = collision
* 0 = no collision
*/
// extern int checkCircleStructureCollision(int index, int x, int z, int radius);

/*
* getStructureSquare
* Gets the (x1,z1) (x2,z2) of a gameObject at
* the given index in the gameObject->structure
* Out:
* 1 = ERROR
* 0 = success
* In:
* (x1,z1) (x2,z2) are updated with respective structures values
*/
extern int getStructureSquare(Item *s, int *x1, int *z1, int *x2, int *z2);

/*
* getStructureXZR
* Gets the x, z, and radius of a gameObject at
* the given index in the gameObject->structure
* Out:
* 1 = ERROR
* 0 = success
* In:
* x, z, radius are updated with respective structures values
*/
// extern int getStructureXZR(int index, int *x, int *z, int *radius);

#endif //msansome_generation_h