/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_linkedlist_h
#define msansome_linkedlist_h

typedef enum item_type
{
    INVALID = 0,
    VALLEY,
    HILL,
    BASE,
    CLOUD,
    METEOR
} item_type;
typedef struct item
{
    item_type type;
    void *ptr;
    struct item *next;
} Item;

typedef struct list
{
    Item *first;
    Item *last;
} List;

/**
 * Allocates memory for List
 * @return pointer to allocated List
 */
List *createList();

/**
 * Adds an item to the end of the list
 * @param list list to add to
 * @param item item to store in list
 * @param type the type of the game item
 */
void addItem(List *list, void *item, item_type type);

/**
 * Removes and returns the first item of the list
 * @param list list to remove from
 * @return first item in list
 */
void *popItem(List *list);

// void removeItemAtIndex(List *list, int index);

/**
 * Get an item from a specified index
 * @param list list to operate on
 * @param index which item to get
 * @return pointer to item in list
 */
Item *getItemAtIndex(List *list, int index);

/**
 * find the number of items in a list
 * @param list list to operate on
 * @return number of items in list
 */
int getListSize(List *list);

/**
 * Free memory of list and all items
 * @param list list to operate on
 */
void freeList(List *list);

#endif //msansome_linkedlist_h