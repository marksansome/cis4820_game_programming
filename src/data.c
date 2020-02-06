/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "config.h"
#include "graphics.h"

ObjectStore *g_structures;
ObjectStore *g_clouds;

int g_num_mobs;

void initWorld()
{
    /* initialize world to empty */
    for (int i = 0; i < WORLDX; i++)
    {
        for (int j = 0; j < WORLDY; j++)
        {
            for (int k = 0; k < WORLDZ; k++)
            {
                world[i][j][k] = 0;
            }
        }
    }
}

void initStructureStore()
{
    g_structures = (ObjectStore *)malloc(sizeof(ObjectStore) + sizeof(Object[MAX_OBJECTS]));
    if (g_structures == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    g_structures->numObj = 0;
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        g_structures->object[i] = NULL;
    }
}

void initCloudStore()
{
    g_clouds = (ObjectStore *)malloc(sizeof(ObjectStore) + sizeof(Object[MAX_CLOUDS]));
    if (g_clouds == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    g_clouds->numObj = 0;
    for (int i = 0; i < MAX_CLOUDS; i++)
    {
        g_clouds->object[i] = NULL;
    }
}

// void initObjectStore(ObjectStore *os, int maxObj)
// {
//     os = (ObjectStore *)malloc(sizeof(ObjectStore) + sizeof(Object[maxObj]));
//     if (os == NULL)
//     {
//         printf("Unable to allocate memory!\n");
//         exit(1);
//     }
//     os->numObj = 0;
//     for (int i = 0; i < maxObj; i++)
//     {
//         os->object[i] = NULL;
//     }
// }

Object *createObject(object_type type, int render, void *ptr)
{
    Object *o = (Object *)malloc(sizeof(Object));
    if (o == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    o->type = type;
    o->render = render;
    o->ptr = ptr;

    return o;
}

void addStructure(Object *o)
{
    //TODO: add error checking here to see if added object excedes max object
    // limit
    g_structures->object[g_structures->numObj] = o;
    g_structures->numObj += 1;
}

void addCloud(Object *o)
{
    //TODO: add error checking here to see if added object excedes max object
    // limit
    g_clouds->object[g_clouds->numObj] = o;
    g_clouds->numObj += 1;
}

void freeObjectStore()
{
    //TODO: handle freeing memory. Call each objects free
    return;
}