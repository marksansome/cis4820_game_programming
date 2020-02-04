/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef __MSANSOME_DATA__
#define __MSANSOME_DATA__

#include "config.h"
#include "graphics.h"

typedef enum object_type
{
    INVALID = 0,
    VALLEY,
    HILL,
    BASE,
    CLOUD,
    PROJECTILE
} object_type;

typedef struct object
{
    object_type type;
    void *ptr;
    int render;
} Object;

typedef struct object_store
{
    int numObj;
    Object *object[];
} ObjectStore;

// typedef struct cloudObjects
// {
//     int numClouds;
//     Cloud *clouds[MAX_CLOUDS];
// } CloudObjects;

// typedef struct projectileObjects
// {
//     int numProjectiles;
//     Structure *projectiles[MAX_PROJECTILES];
// } ProjectileObjects;

extern ObjectStore *g_structures;

extern ObjectStore *g_clouds;

extern ObjectStore *g_projectiles;

/*
* initWorld
* Set the world array to 0
*/
extern void initWorld();

/*
* initObjectStore
* Set gameObjects to 0
*/
extern void initStructureStore();
extern void initCloudStore();

/*
* createObject
* Creates and allocates memory for a game Object
*/
extern Object *createObject(object_type type, int render, void *ptr);

/*
* addObject
* Adds a object to ObjectStore
*/
extern void addStructure(Object *o);

extern void addCloud(Object *o);

/*
* initializeCloudObjects
* Set cloudObjects to 0
*/
// extern void initializeCloudObjects();

/*
* freeObjectStore
* Free memory allocated for all objects in an ObjectStore
*/
extern void freeObjectStore();

#endif // __MSANSOME_DATA__