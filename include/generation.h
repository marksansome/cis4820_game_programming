#ifndef __MSANSOME_GENERATION__
#define __MSANSOME_GENERATION__

#include "graphics.h"
#include "utility.h"
#include "base.h"
#include "cloud.h"
#include "hill.h"
#include "valley.h"

// depth of the ground (top layer will be green)
#define GROUND_DEPTH 5
// size of gameObjects storage
#define MAX_OBJECTS 250
// number of items that will be attempted to generate
// if there is a collision item will not be generated
#define MAX_TERRAIN 150

#define MAX_CLOUDS 1750

typedef enum structureId
{
    id_invalid = 0,
    id_valley,
    id_hill,
    id_base,
    id_cloud
} StructureId;

typedef struct structure
{
    StructureId id;
    void *ptr;
    int render;
} Structure;

typedef struct gameObjects
{
    int numStructures;
    Structure *structures[MAX_OBJECTS];
} GameObjects;

typedef struct cloudObjects
{
    int numClouds;
    Cloud *clouds[MAX_CLOUDS];
} CloudObjects;

extern GameObjects *gameObjects;

extern CloudObjects *cloudObjects;

/*
* initializeWorld
* Set the world array to 0
*/
extern void initializeWorld();

/*
* initializeGameObjects
* Set gameObjects to 0
*/
extern void initializeGameObjects();

/*
* initializeCloudObjects
* Set cloudObjects to 0
*/
extern void initializeCloudObjects();

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
* createStructure
* Creates and allocates memory for a Structure
*/
extern Structure *createStructure(StructureId id, int render, void *ptr);

/*
* addGameObject
* Adds a structure to gameObjects
*/
extern void addGameObject(Structure *s);

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
extern int getStructureSquare(int index, int *x1, int *z1, int *x2, int *z2);

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

/*
* freeStructures
* Free memory allocated for all structures in gameObjects
*/
extern void freeStructures();

#endif // __MSANSOME_GENERATION__