CIS4820 Game Programming - University of Guelph - Winter 2020
---------------------------------------------------------------
Name:     Mark Sansome
Sudent #: 0916066


Assignment 1 - Building a Three Dimensional World
-------------------------------------------------
Due. January 24, 2020

Assignment 2 - Projectiles, Meteors, and Maps
-------------------------------------------------
Due. February 7, 2020


Building the Game
-----------------
To build the game run the following commands:
make

This will produce the games executable: a2

To run the game, run the generated executable:
./a2

Configuration
-------------
All game parameters can be found in 'include/config.h'

Limitation
----------
- Clouds are made up of randomly placed single blocks, they should be full
    large objects. However, they are random and due move with the games
    update functions.

- Although rare, it is possible for meteors to collide with other meteors in
    the air. This causes the meteor to stop and look like it it floating.
