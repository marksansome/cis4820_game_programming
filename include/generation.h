#ifndef __MSANSOME_GENERATION__
#define __MSANSOME_GENERATION__

#include "graphics.h"
#include "utility.h"

#define GROUND_DEPTH 5 // depth of the ground (top layer will be green)

// number of items that will be attempted to generate
// if there is a collision item will not be generated

typedef enum structureId
{
    id_invalid = 0,
    id_valley,
    id_hill,
    id_base
} StructureId;

typedef struct structures
{
    void *ptr;
    StructureId id;
} Structures;

/*
* initializeWorld
* Set the world array to 0
*/
void initializeWorld();

/*
* createTestWorld
* Initalize the game world
* Generate a test world to debug the graphics engine
*/
void createTestWorld();

/*
* createMainWorld
* Initalize the game world
* Generate the games main world environment
*/
void createMainWorld();

void generateHill(Hill);

#endif // __MSANSOME_GENERATION__