# CIS4820 Game Programming - University of Guelph - Winter 2020
------------------------------------------------------------------------------
Name:      Mark Sansome

Student #: 0916066

------------------------------------------------------------------------------
## Assignment 1 - Building a Three Dimensional World

Due. January 24, 2020

------------------------------------------------------------------------------
## Assignment 2 - Projectiles, Meteors, and Maps

Due. February 7, 2020

------------------------------------------------------------------------------
## Assignment 3 - Enemy AI and Animation

Due. March 6, 2020

------------------------------------------------------------------------------
## Assignment 4 - Game Control and Opponent AI

Due. March 27, 2020

------------------------------------------------------------------------------
## Building the Game

To build the game run the following commands:
`make`

This will produce the games executable: a1

To run the game, run the generated executable:
`./a1`

Note: Although this is Assignment 2, the outline says that the executable
    should be named "./a1" as such the name stays as a1, instead of a2

------------------------------------------------------------------------------
## What you need to know

Players team is RED
Opponent team is BLUE

------------------------------------------------------------------------------
## Opponent AI (BLUE TEAM)

A breif description of how the opponent AI is implemented. The AI has a heavier
focus on spawning trucks as this leads to collecting meteors faster. The AI
also tries to place towers to get as close to the players base as possible.

If opponent team's meteor count is greater than 3
    generate random number between 0 and 1
if the generated number is less than 0.75 and the team has less than 10 trucks
    spawn a truck
if the generated number is greater than 0.75 and the team has less than 6 towers
    spawn a tower at the maximum distance from the last tower possible

------------------------------------------------------------------------------
## Configuration

All game parameters can be found in 'include/config.h'

------------------------------------------------------------------------------
## Limitations

- Although rare, it is possible for meteors to collide with other meteors in
    the air. This causes the meteor to stop and look like it's floating.

- If a meteor is detroyed, it can still be collected as the internal reference
    is not removed.

- Towers can spawn on top of each other

- Towers can destroy themselves

- Towers only damage enemy vehicles. No friendly fire

- Vehicles only take damage from projectiles. If a vehicle explodes on another
    vehicle, no damage is taken
