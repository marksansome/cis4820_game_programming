/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

/* Derived from scene.c in the The OpenGL Programming Guide */
/* Keyboard and mouse rotation taken from Swiftless Tutorials #23 Part 2 */
/* http://www.swiftless.com/tutorials/opengl/camera2.html */

/* Frames per second code taken from : */
/* http://www.lighthouse3d.com/opengl/glut/index.php?fps */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "config.h"
#include "data.h"
#include "graphics.h"

#include "base.h"
#include "cloud.h"
#include "generation.h"
#include "hill.h"
#include "map.h"
#include "meteor.h"
#include "projectile.h"
#include "team.h"
#include "utility.h"
#include "valley.h"
#include "vehicle.h"

/* frustum corner coordinates, used for visibility determination  */
extern float corners[4][3];

/* determine which cubes are visible e.g. in view frustum */
extern void ExtractFrustum();
extern void tree(float, float, float, float, float, float, int);

/********* end of extern variable declarations **************/

/*** collisionResponse() ***/
/* -performs collision detection and response */
/*  sets new xyz  to position of the viewpoint after collision */
/* -can also be used to implement gravity by updating y position of vp*/
/* note that the world coordinates returned from getViewPosition()
	   will be the negative value of the array indices */
void collisionResponse()
{
   float buffer = 1.0;
   float x, y, z = 0.0;

   getViewPosition(&x, &y, &z);
   x = x * -1.0;
   y = y * -1.0;
   z = z * -1.0;

   for (float i = x - buffer; i < x + (buffer * 2.0); i += buffer)
   {
      for (float j = y - buffer; j < y + (buffer * 2.0); j += buffer)
      {
         for (float k = z - buffer; k < z + (buffer * 2.0); k += buffer)
         {
            if (world[(int)i][(int)j][(int)k] != 0)
            {
               float ox, oy, oz = 0.0;
               getOldViewPosition(&ox, &oy, &oz);
               setViewPosition(ox, oy, oz);
            }
         }
      }
   }

   // check VP collision with world border
   if (!testWorld)
   {
      if (x >= (WORLDX - 0.15) || x <= 0.15 ||
          z >= (WORLDZ - 0.15) || z <= 0.15 ||
          y >= (WORLDY - WORLD_CLOUD_GAP - 0.15) || y <= 0.15)
      {
         float ox, oy, oz = 0.0;
         getOldViewPosition(&ox, &oy, &oz);
         setViewPosition(ox, oy, oz);
      }
   }
}

/******* draw2D() *******/
/* draws 2D shapes on screen */
/* use the following functions: 			*/
/*	draw2Dline(int, int, int, int, int);		*/
/*	draw2Dbox(int, int, int, int);			*/
/*	draw2Dtriangle(int, int, int, int, int, int);	*/
/*	set2Dcolour(float []); 				*/
/* colour must be set before other functions are called	*/
void draw2D()
{
   GLfloat black[] = {0.0, 0.0, 0.0, 0.5};
   GLfloat green[] = {0.0, 0.5, 0.0, 0.5};

   if (testWorld)
   {
      /* draw some sample 2d shapes */
      if (displayMap == 1)
      {
         set2Dcolour(green);
         draw2Dline(0, 0, 500, 500, 15);
         draw2Dtriangle(0, 0, 200, 200, 0, 200);
         set2Dcolour(black);
         draw2Dbox(500, 380, 524, 388);
      }
   }
   else
   {
      if (displayMap == 1)
      {
         // calculate map position
         int mapSize = ((screenWidth / MAP_SMALL_SCALE) / WORLDX) * WORLDX; // must ensure this is a multiple of 100
         int blockSize = mapSize / WORLDX;                                  // take the mapsize divided by the number of drawn blocks
         int buffer = (mapSize / MAP_SMALL_BUFFER);                         // used to set map position away from side of the screen
         int mapOffsetW = screenWidth - buffer - mapSize;                   // map width offset, where to draw map
         int mapOffsetH = screenHeight - buffer;                            // map height offset, where to draw map

         // draw viewpoint
         mapDrawViewPosition(mapOffsetW, mapOffsetH, blockSize);

         // draw world
         mapDrawWorld(mapOffsetW, mapOffsetH, blockSize);

         // draw world border line
         set2Dcolour(black);
         draw2Dline(mapOffsetW - blockSize, mapOffsetH - mapSize, mapOffsetW + mapSize + blockSize, mapOffsetH - mapSize, 5);                   // bottom
         draw2Dline(mapOffsetW - blockSize, mapOffsetH + (2 * blockSize), mapOffsetW - blockSize, mapOffsetH - mapSize, 5);                     // left
         draw2Dline(mapOffsetW + mapSize + blockSize, mapOffsetH + (2 * blockSize), mapOffsetW + mapSize + blockSize, mapOffsetH - mapSize, 5); // right
         draw2Dline(mapOffsetW - blockSize, mapOffsetH + (2 * blockSize), mapOffsetW + mapSize + blockSize, mapOffsetH + (2 * blockSize), 5);   // top
      }
      else if (displayMap == 2)
      {
         // calculate map position
         int mapSize = ((screenWidth / MAP_LARGE_SCALE) / WORLDX) * WORLDX; // must ensure this is a multiple of 100
         int blockSize = mapSize / WORLDX;                                  // take the mapsize divided by the number of drawn blocks
         int mapOffsetW = (screenWidth - mapSize) / 2;                      // map width offset, where to draw map
         int mapOffsetH = (screenHeight - mapSize) / 2;                     // map height offset, where to draw map

         // draw viewpoint
         mapDrawViewPosition(mapOffsetW, mapOffsetH + (mapSize - (2 * blockSize)), blockSize);

         // draw world
         mapDrawWorld(mapOffsetW, mapOffsetH + (mapSize - (2 * blockSize)), blockSize);

         // draw world border line
         set2Dcolour(black);
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH - blockSize - (blockSize / 2), mapOffsetW + mapSize + (blockSize / 2), mapOffsetH - blockSize - (blockSize / 2), 15);         // bottom
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH - blockSize - (blockSize / 2), mapOffsetW - (blockSize / 3), mapOffsetH + mapSize - (blockSize / 2), 15);                     // left
         draw2Dline(mapOffsetW + mapSize + (blockSize / 3), mapOffsetH - blockSize - (blockSize / 2), mapOffsetW + mapSize + (blockSize / 3), mapOffsetH + mapSize - (blockSize / 2), 15); // right
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH + mapSize - (blockSize / 1.5), mapOffsetW + mapSize + (blockSize / 2), mapOffsetH + mapSize - (blockSize / 1.5), 15);         // top
      }
   }
}

/*** update() ***/
/* background process, it is called when there are no other events */
/* -used to control animations and perform calculations while the  */
/*  system is running */
/* -gravity must also implemented here, duplicate collisionResponse */
void update()
{
   int i, j, k;
   float *la;
   float x, y, z;

   /* update old position so it contains the correct value */
   /* -otherwise view position is only correct after a key is */
   /*  pressed and keyboard() executes. */
   getViewPosition(&x, &y, &z);
   setOldViewPosition(x, y, z);

   /* sample animation for the testworld, don't remove this code */
   /* demo of animating mobs */
   if (testWorld)
   {

#if 0
// Fire a ray in the direction of forward motion
float xx, yy, zz;
getViewPosition(&x, &y, &z);
getOldViewPosition(&xx, &yy, &zz);
printf("%f %f %f %f %f %f\n", xx, yy, zz, x, y, z);
printf("%f %f %f\n",  -xx+((x-xx)*25.0), -yy+((y-yy)*25.0), -zz+((z-zz)*25.0));
createTube(2, -xx, -yy, -zz, -xx-((x-xx)*25.0), -yy-((y-yy)*25.0), -zz-((z-zz)*25.0), 5);
#endif

      /* sample of rotation and positioning of mob */
      /* coordinates for mob 0 */
      static float mob0x = 50.0, mob0y = 25.0, mob0z = 52.0;
      static float mob0ry = 0.0;
      static int increasingmob0 = 1;
      /* coordinates for mob 1 */
      static float mob1x = 50.0, mob1y = 25.0, mob1z = 52.0;
      static float mob1ry = 0.0;
      static int increasingmob1 = 1;
      /* counter for user defined colour changes */
      static int colourCount = 0;
      static GLfloat offset = 0.0;

      /* move mob 0 and rotate */
      /* set mob 0 position */
      setMobPosition(0, mob0x, mob0y, mob0z, mob0ry);

      /* move mob 0 in the x axis */
      if (increasingmob0 == 1)
         mob0x += 0.2;
      else
         mob0x -= 0.2;
      if (mob0x > 50)
         increasingmob0 = 0;
      if (mob0x < 30)
         increasingmob0 = 1;

      /* rotate mob 0 around the y axis */
      mob0ry += 1.0;
      if (mob0ry > 360.0)
         mob0ry -= 360.0;

      /* move mob 1 and rotate */
      setMobPosition(1, mob1x, mob1y, mob1z, mob1ry);

      /* move mob 1 in the z axis */
      /* when mob is moving away it is visible, when moving back it */
      /* is hidden */
      if (increasingmob1 == 1)
      {
         mob1z += 0.2;
         showMob(1);
      }
      else
      {
         mob1z -= 0.2;
         hideMob(1);
      }
      if (mob1z > 72)
         increasingmob1 = 0;
      if (mob1z < 52)
         increasingmob1 = 1;

      /* rotate mob 1 around the y axis */
      mob1ry += 1.0;
      if (mob1ry > 360.0)
         mob1ry -= 360.0;

      /* change user defined colour over time */
      if (colourCount == 1)
         offset += 0.05;
      else
         offset -= 0.01;
      if (offset >= 0.5)
         colourCount = 0;
      if (offset <= 0.0)
         colourCount = 1;
      setUserColour(9, 0.7, 0.3 + offset, 0.7, 1.0, 0.3, 0.15 + offset, 0.3, 1.0);

      /* sample tube creation  */
      /* draws a purple tube above the other sample objects */
      createTube(1, 45.0, 30.0, 45.0, 50.0, 30.0, 50.0, 6);

      /* end testworld animation */
   }
   else
   {
      static double cloudTime, meteorTime = 0.0;
      struct timeval tv;
      gettimeofday(&tv, NULL);

      double curTime = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

      // cloud movement
      if (curTime - cloudTime >= CLOUD_SPEED)
      {
         cloudTime = curTime;

         // clean cloud level
         for (int i = 0; i < WORLDX; i++)
         {
            for (int k = 0; k < WORLDZ; k++)
            {
               world[i][CLOUD_LEVEL][k] = 0;
            }
         }

         for (int i = 0; i < getListSize(g_clouds); i++)
         {
            Cloud *c = getItemAtIndex(g_clouds, i)->ptr;
            moveCloud(c);
         }
      }

      // player projectile movement and collision
      if (curTime - g_player_projectile->timeTracker >= PROJECTILE_SPEED)
      {
         g_player_projectile->timeTracker = curTime;
         moveProjectile(g_player_projectile);
      }

      // generate new meteors
      if (curTime - meteorTime >= METEOR_SPAWN_TIME)
      {
         meteorTime = curTime;

         for (int i = 0; i < METEOR_PER_SPAWN; i++)
         {
            Meteor *m = createMeteor();
            initializeMeteor(m);
            addItem(g_falling_meteors, m, METEOR);
         }
      }

      // move existing meteors
      for (int i = 0; i < getListSize(g_falling_meteors); i++)
      {
         Meteor *m = getItemAtIndex(g_falling_meteors, i)->ptr;
         if (curTime - m->timeTracker >= m->velocity)
         {
            m->timeTracker = curTime;
            if (m->isFalling)
            {
               moveMeteor(m);
            }
            else
            {
               // move meteor to g_meteors
               Meteor *ret = removeItemAtIndex(g_falling_meteors, i)->ptr;
               addItem(g_meteors, ret, METEOR);
            }
         }
      }

      // to make it more fair, we randomly select which team is updated first
      if (rand() % 2)
      {
         updateTeam(g_red_team, curTime, g_blue_team->vehicles, g_meteors, g_falling_meteors);
         // debug:
         // updateTeam(g_red_team, curTime, g_red_team->vehicles, g_meteors, g_falling_meteors);
      }
      else
      {
         updateTeam(g_blue_team, curTime, g_red_team->vehicles, g_meteors, g_falling_meteors);
         // debug:
         // updateTeam(g_blue_team, curTime, g_blue_team->vehicles, g_meteors, g_falling_meteors);
      }

      // check teams win conditions
      if (getListSize(g_red_team->meteors) >= WIN_SCORE)
      {
         printf("**********************************\n");
         printf("         RED team has won!        \n");
         printf("**********************************\n");
         //! @todo free memory
         exit(0);
      }
      if (getListSize(g_blue_team->meteors) >= WIN_SCORE)
      {
         printf("**********************************\n");
         printf("        BLUE team has won!        \n");
         printf("**********************************\n");
         //! @todo free memory
         exit(0);
      }
      // debug
      // printf("red score %d\n", getListSize(g_red_team->meteors));
      // printf("blue score %d\n", getListSize(g_blue_team->meteors));
   }
}

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */
void mouse(int button, int state, int x, int y)
{
   // if button pressed, fire projectile
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      if (!g_player_projectile->inMotion)
      {
         setProjectileToViewPosition(g_player_projectile);
      }
      fireProjectile(g_player_projectile);
   }
}

int main(int argc, char **argv)
{
   /* Intializes random number generator */
   time_t t;
   srand((unsigned)time(&t));

   // initialize the graphics system
   graphicsInit(&argc, argv);

   // initialize world to empty
   initializeWorld();

   // initialize global tracking values
   g_num_mobs = 0;

   // create player projectile
   g_player_projectile = createProjectile();

   // create user defined colours
   createUserColours();

   // create worlds game objects storage
   g_structures = createList();
   g_clouds = createList();
   g_meteors = createList();
   g_falling_meteors = createList();

   // create team object storage
   g_red_team = createTeam();
   initializeTeam(g_red_team, RED_TEAM);
   g_blue_team = createTeam();
   initializeTeam(g_blue_team, BLUE_TEAM);

   if (testWorld == 1)
   {
      /* Builds a sample world which will be used for testing */
      /* The testworld is only guaranteed to work with world
      dimensions of 100,50,100 */
      createTestWorld();
   }
   else
   {
      createMainWorld();
   }

   /* starts the graphics processing loop */
   /* code after this will not run until the program exits */
   glutMainLoop();

   // freeObjectStore();
   free(g_structures);
   free(g_clouds);
   free(g_meteors);
   free(g_falling_meteors);
   free(g_red_team);
   free(g_blue_team);
   free(g_player_projectile);

   return 0;
}
