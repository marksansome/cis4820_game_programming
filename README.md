# CIS4820 Game Programming - University of Guelph - Winter 2020

## Deliverables

### Assignment 1 - Building a Three Dimensional World

Due. January 24, 2020

### Assignment 2 - Projectiles, Meteors, and Maps

Due. February 7, 2020

### Assignment 3 - Enemy AI and Animation

Due. March 6, 2020

### Assignment 4 - Game Control and Opponent AI

Due. March 27, 2020

## Building the Game

To build the game run the following commands:
`make`

This will produce the games executable: `a1`

To start the game run the generated executable:
`./a1`

Additional command line arguments are as follows:
`-full`         run in fullscreen.
`-testworld`    start with a simple world to demonstrate the system
`-fps`          print the frames per second being displayed
`-help`         print a list of command line arguments
`-drawall`      draw all cubes in the world without using visible surface
                    detection to remove none visible cubes (very slow).

To quickly see the engine running you can type `./a1 -testworld`.
You can run it in fullscreen using `./a1 -testworld -full`.

Note: To build this game on older versions of MACOS it may be required to
    change where the compiler looks for frameworks such as OpenGL and GLUT.
    Please look at `./Makefile` and the `INCLUDE_FRAMEWORK` variable.

Note: The outline states that the executable must be named "./a1"

## What you need to know

Players team is RED
Opponent team is BLUE

### Controls

`q` key used to exit the game.

`m` key used to toggle the minimap size.

`t` key used to spawn a new truck, costs 1 meteor. Trucks have 2 health.

`y` key used to spawn a new tower, costs 2 meteors.
    When `y` is pressed a placement marker will appear on the ground. Towers
    can only be placed in a 10 block radius from another tower or base. If
    the placement marker is in this block radius it will be appear green. If
    the placement marker is outside this radius it will appear yellow. If `y`
    is pressed again while the marker is in the block radius, and the player
    has enough meteors, a tower will be built.

`left mouse click` used to fire a projectile from the players viewpoint. This
    can be used to remove blocks from the world and attack vehicles. If a
    vehicle is hit several times by any projectile (player or tower) they
    are destroyed.

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

## Configuration

All game parameters can be found in `./include/config.h`

## Limitations

- Meteors can collide with other meteors in the air. This causes the meteor to
    stop mid-air.

- If a meteor is detroyed, it can still be collected as the internal reference
    is not removed.

- Towers can spawn on top of each other.

- Towers can occasionaly hit themselves if the target is to close to the
    tower's base.

- Towers can only damage enemy vehicles. No friendly fire.

- Towers do not target other towers.

- Towers cannot be destroyed.

- Vehicles only take damage from projectiles. If a vehicle explodes on another
    vehicle, no damage is taken.
