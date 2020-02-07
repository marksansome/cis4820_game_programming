/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "data.h"
#include "graphics.h"
#include "linkedList.h"

ObjectStore *g_structures;
ObjectStore *g_clouds;

List *g_structureList;

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

ObjectStore *createObjectStore(int maxObj)
{
    ObjectStore *os = (ObjectStore *)malloc(sizeof(ObjectStore) + sizeof(Object[maxObj]));
    if (os == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }
    os->numObj = 0;
    for (int i = 0; i < maxObj; i++)
    {
        os->object[i] = NULL;
    }

    return os;
}

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
    //! @todo add error checking here to see if added object excedes max object
    // limit
    g_structures->object[g_structures->numObj] = o;
    g_structures->numObj += 1;
}

void addCloud(Object *o)
{
    //! @todo add error checking here to see if added object excedes max object
    // limit
    g_clouds->object[g_clouds->numObj] = o;
    g_clouds->numObj += 1;
}

void freeObjectStore()
{
    //! @todo handle freeing memory. Call each objects free
    return;
}