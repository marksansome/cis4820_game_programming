/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_team_h
#define msansome_team_h

typedef enum team
{
    INVALID_TEAM = 0,
    RED_TEAM,
    BLUE_TEAM
} Team;

/**
 * Gets a random offset in teams spawn zone
 * @param team team type (RED, BLUE)
 * @return x position in world array for structure
 */
extern int getTeamOffset(Team team);

#endif // msansome_team_h
