/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_vehicle_h
#define msansome_vehicle_h

#include "meteor.h"
#include "team.h"
#include "utility.h"

typedef enum vehicle_type
{
    INVALID_VEHICLE = 0,
    TRUCK_VEHICLE
} vehicle_type;

typedef enum vehicle_state
{
    INVALID_VEHICLE_STATE = 0,
    SEARCHING_VEHICLE_STATE, // searching for meteor
    MOVING_VEHICLE_STATE,    // found meteor within 10 blocks, moving to it
    LOADING_VEHICLE_STATE,   // next to meteor, loading
    RETURNING_VEHICLE_STATE  // returning to base
} vehicle_state;

typedef struct vehicle
{
    vehicle_type type;    // type of vehicle
    vehicle_state state;  // current state of vehicle
    int colour;           // colour to be drawn
    int health;           // amount of health remaining
    int height;           // height of the vehicle
    int y;                // current elevation
    int x1, z1;           // current starting point to be drawn
    int x2, z2;           // current end point to be drawn
    int xTarget, zTarget; // movement destination
    int isCarryingMeteor; // is the vehicle is carrying a meteor
    Meteor *targetMeteor; // meteor that is current being targeted
    double timeTracker;   // keep track of the last time Vehicle moved
    double speed;         // time between movement, in milliseconds
    double baseSpeed;     // original base time between movement, in milliseconds
} Vehicle;

/**
 * Allocates memory for a Vehicle struct
 * @return pointer to allocated Vehicle
 */
extern Vehicle *createVehicle();

/**
 * Initializes values in a Vehicle
 * @param vehicle pointer to allocated Vehicle
 * @param type type of vehicle
 * @param team pointer to vehicles associated Team
 */
extern void initializeVehicle(Vehicle *vehicle, vehicle_type type, Team *team);

/**
 * Draws Vehicle in the world array
 * @param vehicle pointer to allocated Vehicle
 * @param teamType team the vehicle is associated with
 * @param isEmpty if true, set all blocks to colour EMPTY
 */
extern void generateVehicle(Vehicle *vehicle, team_type teamType, int isEmpty);

/**
 * Moves a Vehicle to the next space
 * @param vehicle Vehicle to be moved
 * @param team Team vehicle is owned by
 * @param meteors List of meteors to check distance to
 */
extern void moveVehicle(Vehicle *vehicle, Team *team, List *meteors);

/**
 * Resets a vehicle to its original starting state
 * @param vehicle Vehicle to be updated
 * @param team Team vehicle is owned by
 */
extern void setSearchingState(Vehicle *v, Team *t);

/**
 * Incements a Vehicle's values to the next space
 * @param vehicle Vehicle to be moved
 */
extern void incrementVehicle(Vehicle *v);

/**
 * Checks a Vehicle's empty spaces to determine damage
 * @param vehicle Vehicle to be moved
 */
extern void updateVehicleDamage(Vehicle *v, int index, Team *t);

/**
 * Removes a Vehicle from the world
 * @param vehicle Vehicle to be un-generated
 */
extern void removeVehicle(Vehicle *v);

/**
 * Frees the memory for a Vehicle
 * @param vehicle pointer to allocated Vehicle
 */
extern void freeVehicle(Vehicle *vehicle);

#endif //msansome_vehicle_h