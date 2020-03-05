/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_team_h
#define msansome_team_h

#include "base.h"
#include "linkedList.h"
#include "utility.h"

typedef enum team_type
{
    INVALID_TEAM = 0,
    RED_TEAM,
    BLUE_TEAM
} team_type;

typedef struct team
{
    team_type type;
    Base *base;
    List *vehicles;
    List *towers;
    List *meteors;
    int colour;
} Team;

/**
 * Allocate memory for a Team struct
 * @return pointer to allocated Team
 */
extern Team *createTeam();

/**
 * Initializes values in a Team
 * @param team pointer to allocated Team
 * @param type team type
 */
extern void initializeTeam(Team *team, team_type type);

/**
 * Initializes Teams starting objects (vehicles, towers, etc)
 * @param team pointer to allocated Team
 */
extern void initializeTeamStartingObjects(Team *t);

/**
 * Checks if the square defined by (x1,z1) (x2,z2)
 * is on top of the teams other objects
 * @param team team to check against
 * @param y position of the bottom edge
 * @param x1 position of starting x
 * @param z1 position of starting z
 * @param x2 position of ending x
 * @param z2 position of ending z
 * @return 1 = collision, 0 = no collision
 */
extern int checkTeamCollision(Team *team, int y, int x1, int z1, int x2, int z2);

/**
 * Places the meteors collected for the team in
 * a stack next to the team base
 * @param team team to draw meteors
 */
extern void drawMeteorCube(Team *t);

/**
 * Gets a random offset in teams spawn zone
 * @param team team type (RED, BLUE)
 * @return x position in world array for structure
 */
extern int getTeamOffset(team_type team);

#endif // msansome_team_h
