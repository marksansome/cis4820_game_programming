/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_config_h
#define msansome_config_h

// BASE
#define BASE_HEIGHT 3
#define BASE_EDGE_LENGTH 5

// CLOUD
#define CLOUD_LEVEL 48     // y level clouds are generated
#define MAX_CLOUDS 1750    // maximum number of clouds that is able to be created
#define CLOUD_SPEED 300.00 // milliseconds per movement

// GENERATION
#define GROUND_DEPTH 5  // depth of the ground (top layer will be green)
#define MAX_OBJECTS 250 // size of gameObjects storage
#define MAX_TERRAIN 150 // number of world objects that will be attempted to generate

// HILL
#define MIN_HILL_HEIGHT 2  // minimum height of a hill
#define MAX_HILL_HEIGHT 3  // maximum height of a hill
#define MIN_HILL_RADIUS 6  // minimum radius of a hill
#define MAX_HILL_RADIUS 12 // maximum radius of a hill

// METEOR
#define STARTING_METEORS 30
#define METEOR_STARTING_Y 60
#define METEOR_EDGE_BUFFER 5
#define MAX_METEOR_SPEED 30.0
#define MIN_METEOR_SPEED 100.0
#define METEOR_SPAWN_TIME 10000.0 // time until next meteors spawn
#define METEOR_PER_SPAWN 0        // number of meteors that spawn per spawn time

// MINI MAP
#define MAP_SMALL_BUFFER 10 // buffer scale from screen edge
#define MAP_LARGE_BUFFER 4
#define MAP_SMALL_SCALE 8
#define MAP_LARGE_SCALE 2

// PROJECTILE
#define PROJECTILE_SPEED 30.0 // milliseconds per movement

// UTILITY

// VALLEY
#define MIN_VALLEY_DEPTH 2   // minimum height of a valley
#define MAX_VALLEY_DEPTH 3   // maximum height of a valley
#define MIN_VALLEY_RADIUS 6  // minimum radius of a valley
#define MAX_VALLEY_RADIUS 12 // maximum radius of a valley

// WORLD
#define WORLDX 100
#define WORLDY 50
#define WORLDZ 100
#define WORLD_CLOUD_GAP 3

#endif //msansome_config_h
