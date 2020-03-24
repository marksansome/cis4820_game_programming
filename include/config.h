/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_config_h
#define msansome_config_h

// GAME
#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1536
// #define SCREEN_WIDTH 1024
// #define SCREEN_HEIGHT 768
#define WIN_SCORE 27 // number of meteors needed to win the game

// AI
#define AI_START_METEORS 3 // number of meteors needed before AI starts buying towers/vehicles
#define AI_MAX_TOWERS 6    // maximum number of towers the AI will buy
#define AI_MAX_VEHICLES 10 // maximum number of trucks the AI will buy

// BASE
#define BASE_HEIGHT 3            // y height of base
#define BASE_EDGE_LENGTH 5       // x and z length of the edge for the square base
#define BASE_STORAGE_Z_OFFSET 20 // z offset to account for adding vehicles and meteor cube

// CLOUD
#define CLOUD_LEVEL 48     // y level clouds are generated
#define MAX_CLOUDS 30      // maximum number of clouds that is able to be created
#define MIN_CLOUD_RADIUS 4 // minimum radius of a cloud
#define MAX_CLOUD_RADIUS 8 // maximum radius of a cloud
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
#define STARTING_METEORS 20       // number of meteors that fall at start of game, this also includes METEOR_PER_SPAWN
#define METEOR_STARTING_Y 60      // starting y position for all meteors
#define METEOR_EDGE_BUFFER 4      // buffer distance from the world edge where meteors will not spawn
#define MAX_METEOR_SPEED 30.0     // maximum meteor speed, in milliseconds
#define MIN_METEOR_SPEED 100.0    // minimum meteor speed, in milliseconds
#define METEOR_SPAWN_TIME 10000.0 // time until next meteors spawn, in milliseconds
#define METEOR_PER_SPAWN 10       // number of meteors that spawn per spawn time

// METEOR SCORE
#define METEOR_SCORE_BUFFER 20 // buffer scale from screen edge for meteor score
#define METEOR_SCORE_SCALE 100 // meteor score size scale
#define METEOR_SCORE_SPACE 5   // meteor score size scale

// MINI MAP
#define MAP_SMALL_BUFFER 10 // buffer scale from screen edge
#define MAP_SMALL_SCALE 8   // small map size scale
#define MAP_LARGE_SCALE 2   // large map size scale

// PROJECTILE
#define PROJECTILE_SPEED 20.0 // milliseconds per movement

// TEAM
#define MIN_RED_TEAM_X_OFFSET 5   // minimum distance from map edge to spawn team structures (base, vehicle)
#define MAX_RED_TEAM_X_OFFSET 10  // maximum distance from map edge to spawn team structures (base, vehicle)
#define MIN_BLUE_TEAM_X_OFFSET 85 // minimum distance from map edge to spawn team structures (base, vehicle)
#define MAX_BLUE_TEAM_X_OFFSET 90 // maximum distance from map edge to spawn team structures (base, vehicle)
#define MAX_TEAM_Z_OFFSET 10      // maximum distance from map edge to spawn team structures (base, vehicle)
#define NUM_STARTING_TOWERS 0     // number of starting towers per team
#define NUM_STARTING_TRUCKS 1     // number of starting truck vehicles per team

// TOWER
#define TOWER_TO_BASE_OFFSET 20 // distance in front of base to place starting towers
#define TOWER_HEIGHT 4          // height of the tower
#define TOWER_EDGE_LENGTH 1     // edge length of a tower
#define TOWER_SEARCH_RADIUS 10  // radius to search for enemy vehicles
#define TOWER_PLACE_RADIUS 10   // radius to place for team towers
#define TOWER_BUILD_COST 2      // cost, in meteors, to build a tower

// UTILITY
#define MAX_ATTEMPTS_TO_PLACE_OBJECT 10

// VALLEY
#define MIN_VALLEY_DEPTH 2   // minimum height of a valley
#define MAX_VALLEY_DEPTH 3   // maximum height of a valley
#define MIN_VALLEY_RADIUS 6  // minimum radius of a valley
#define MAX_VALLEY_RADIUS 12 // maximum radius of a valley

// VEHICLE
#define VEHICLE_OFFSET 3         // distance between each vehicle
#define VEHICLE_METEOR_RADIUS 10 // search radius for meteors
#define TRUCK_EDGE_LENGTH 3      // edge length of a truck
#define TRUCK_HEIGHT 2           // height of a truck
#define TRUCK_HEALTH 2           // amount of damage the truck can take
#define TRUCK_BLOCK_COUNT 10     // number of blocks that make up a truck (not including meteor)
#define TRUCK_SPEED 200.0        // milliseconds per movement
#define TRUCK_BUILD_COST 1       // cost, in meteors, to build a truck

// WORLD
#define WORLDX 100        // x size of the map
#define WORLDY 50         // y size of the map
#define WORLDZ 100        // z size of the map
#define WORLD_CLOUD_GAP 3 // distance from top of the world reserved for clouds

#endif //msansome_config_h
