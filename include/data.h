/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef msansome_data_h
#define msansome_data_h

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

extern int g_num_mobs;

/*
* initWorld
* Set the world array to 0
*/
extern void initWorld();

/*
* initStructureStore
* Set g_structures to 0
*/
extern void initStructureStore();

/*
* initCloudStore
* Set g_clouds to 0
*/
extern void initCloudStore();

/*
* createObject
* Creates and allocates memory for a game Object
*/
extern Object *createObject(object_type type, int render, void *ptr);

/*
* addStructure
* Adds an object to g_structures
*/
extern void addStructure(Object *o);

/*
* addCloud
* Adds an object to g_cloud
*/
extern void addCloud(Object *o);

/*
* freeObjectStore
* Free memory allocated for all objects in an ObjectStore
*/
extern void freeObjectStore();

#endif //msansome_data_h