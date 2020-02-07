/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

List *createList()
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    list->first = NULL;
    list->last = NULL;

    return list;
}

void addItem(List *list, void *ptr)
{
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL)
    {
        printf("Unable to allocate memory!\n");
        exit(1);
    }

    if (list->first == NULL)
    {
        list->first = item;
    }
    else
    {
        list->last->next = item;
    }

    item->ptr = ptr;
    list->last = item;
}

void *popItem(List *list)
{
    Item *item = list->first;
    Item *after = item->next;

    if (list->first != NULL)
    {
        void *ptr = list->first->ptr;
        free(item);
        list->first = after;
        return ptr;
    }
    return NULL;
}

void *getItemAtIndex(List *list, int index)
{
    Item *item = list->first;
    if (item == NULL)
    {
        return NULL;
    }

    for (int i = 0; i <= index; i++)
    {
        if (i == index)
        {
            return item->ptr;
        }
        if (item == list->last)
        {
            return NULL;
        }
        item = item->next;
    }

    return NULL;
}

int getListSize(List *list)
{
    int count = 0;
    Item *item = list->first;

    while (item != NULL)
    {
        count++;
        if (item == list->last)
        {
            return count;
        }
        item = item->next;
    }

    return count;
}

void freeList(List *list)
{
    Item *item = list->first;
    Item *next;

    while (item != NULL)
    {
        if (item == list->last)
        {
            free(item);
            item = NULL;
        }
        else
        {
            next = item->next;
            free(item);
            item = next;
        }
    }

    free(list);
}
