#ifndef __MSANSOME_GENERATION__
#define __MSANSOME_GENERATION__

#include "graphics.h"
#include "utility.h"
#include "hill.h"
#include "valley.h"

#define GROUND_DEPTH 5 // depth of the ground (top layer will be green)
#define MAX_OBJECTS 250
#define MAX_TERRAIN 30

// number of items that will be attempted to generate
// if there is a collision item will not be generated

typedef enum structureId
{
    id_invalid = 0,
    id_valley,
    id_hill,
    id_base
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

extern GameObjects *gameObjects;

/*
* initializeWorld
* Set the world array to 0
*/
extern void initializeWorld();

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
* checkStructureCollision
* Checks if the values collide with any
* other structure in gameObjects. Exclude its own index
* Out:
* 1 = collision
* 0 = no collision
*/
extern int checkStructureCollision(int index, int x, int z, int radius);

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
extern int getStructureXZR(int index, int *x, int *z, int *radius);

/*
* freeStructures
* Free memory allocated for all structures in gameObjects
*/
extern void freeStructures();

#endif // __MSANSOME_GENERATION__