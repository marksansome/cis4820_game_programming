/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_vehicle_h
#define msansome_vehicle_h

typedef struct vehicle
{
    int colour;
    int y;
    int x1;
    int z1;
    int x2;
    int z2;
} Vehicle;

/**
 * Allocates memory for a Vehicle struct
 * @return pointer to allocated Vehicle
 */
extern Vehicle *createVehicle();

/**
 * Initializes values in a Vehicle
 * @param vehicle pointer to allocated Vehicle
 */
extern void initializeVehicle(Vehicle *vehicle);

/**
 * Draws Vehicle in the world array
 * @param vehicle pointer to allocated Vehicle
 */
extern void generateVehicle(Vehicle *vehicle);

/**
 * Frees the memory for a Vehicle
 * @param vehicle pointer to allocated Vehicle
 */
extern void freeVehicle(Vehicle *vehicle);

#endif //msansome_vehicle_h