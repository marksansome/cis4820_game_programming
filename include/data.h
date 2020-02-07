/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_data_h
#define msansome_data_h

#include "linkedList.h"
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

extern ObjectStore *g_structures;
extern ObjectStore *g_clouds;

List *g_meteors;

extern int g_num_mobs;

/**
* Set the world array to 0
*/
extern void initWorld();

/**
* Allocates memory and initalizes an ObjectStore
* @param maxObj size of object array
* @return pointer to allocated ObjectStore
*/
extern ObjectStore *createObjectStore(int maxObj);

/*
* createObject
* Creates and allocates memory for a game Object
*/
extern Object *createObject(object_type type, int render, void *ptr);

extern void addObject(ObjectStore *os, Object *o);

/*
* freeObjectStore
* Free memory allocated for all objects in an ObjectStore
*/
extern void freeObjectStore();

#endif //msansome_data_h