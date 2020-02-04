/* CIS4820 Game Programming - Winter 2020
 * Mark Sansome
 * 0916066
*/

#ifndef __MSANSOME_CONFIG__
#define __MSANSOME_CONFIG__

// BASE
#define BASE_HEIGHT 3
#define BASE_EDGE_LENGTH 5

// CLOUD
#define CLOUD_LEVEL 48
#define MAX_CLOUDS 1750

// GENERATION
#define GROUND_DEPTH 5  // depth of the ground (top layer will be green)
#define MAX_OBJECTS 250 // size of gameObjects storage
#define MAX_TERRAIN 150 // number of world objects that will be attempted to generate

// WORLD
#define WORLDX 100
#define WORLDY 50
#define WORLDZ 100
#define WORLD_CLOUD_GAP 3

// HILL
#define MIN_HILL_HEIGHT 2
#define MAX_HILL_HEIGHT 3
#define MIN_HILL_RADIUS 6
#define MAX_HILL_RADIUS 12

// VALLEY
#define MIN_VALLEY_DEPTH 2
#define MAX_VALLEY_DEPTH 3
#define MIN_VALLEY_RADIUS 6
#define MAX_VALLEY_RADIUS 12

// PROJECTILE
#define MAX_PROJECTILES 1

// UTILITY

#endif // __MSANSOME_CONFIG__