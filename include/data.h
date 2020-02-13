/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_data_h
#define msansome_data_h

#include "linkedList.h"

extern List *g_structures;
extern List *g_clouds;
extern List *g_meteors;

extern int g_num_mobs;

/**
* Set the world array to 0
*/
extern void initializeWorld();

#endif //msansome_data_h