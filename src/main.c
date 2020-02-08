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
#include "meteor.h"
#include "projectile.h"
#include "utility.h"
#include "valley.h"

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
   float buffer = 0.1;
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
      if (x >= (WORLDX - 1.15) || x <= 0.15 ||
          z >= (WORLDZ - 1.15) || z <= 0.15 ||
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
   GLfloat white[] = {1, 1, 1, 1};
   GLfloat green[] = {0.0, 0.5, 0.0, 1};

   if (testWorld)
   {
      /* draw some sample 2d shapes */
      if (displayMap == 1)
      {
         GLfloat green[] = {0.0, 0.5, 0.0, 0.5};
         set2Dcolour(green);
         draw2Dline(0, 0, 500, 500, 15);
         draw2Dtriangle(0, 0, 200, 200, 0, 200);

         set2Dcolour(black);
         draw2Dbox(500, 380, 524, 388);
      }
   }
   else
   {
      //! @todo add minimap
      if (displayMap == 1)
      {
         int mapSize = ((screenWidth / MAP_SMALL_SCALE) / WORLDX) * WORLDX;
         int blockSize = mapSize / WORLDX; // take the mapsize divided by the number of drawn blocks
         int buffer = (mapSize / MAP_SMALL_BUFFER);
         int mapOffsetW = screenWidth - buffer - mapSize;
         int mapOffsetH = screenHeight - buffer - mapSize;

         // draw viewpoint
         float vpX, vpY, vpZ = 0.0;
         getViewPosition(&vpX, &vpY, &vpZ);
         vpX *= -1.0;
         vpZ *= -1.0;
         set2Dcolour(white);
         draw2Dbox(mapOffsetW + (blockSize * (int)vpX),
                   mapOffsetH + (blockSize * (int)vpZ),
                   mapOffsetW + (blockSize * (int)vpX) + blockSize,
                   mapOffsetH + (blockSize * (int)vpZ) + blockSize);

         // draw world
         for (int y = WORLDY - 2; y >= 0; y--) // minus 2 to ensure we don't check out of array bounds
         {
            for (int x = 0; x < WORLDX - 1; x++)
            {
               for (int z = 0; z < WORLDZ - 1; z++)
               {
                  if (world[x][y][z] != 0 && y != CLOUD_LEVEL)
                  {
                     if (world[x][y + 1][z] == 0)
                     {
                        GLfloat ambRed, ambGreen, ambBlue, ambAlpha, difRed, difGreen, difBlue, difAlpha;
                        getUserColour(world[x][y][z], &ambRed, &ambGreen, &ambBlue, &ambAlpha, &difRed, &difGreen, &difBlue, &difAlpha);
                        float colour[4] = {ambRed, ambGreen, ambBlue, ambAlpha};
                        set2Dcolour(colour);
                        draw2Dbox(mapOffsetW + (blockSize * x),
                                  mapOffsetH + (blockSize * z),
                                  mapOffsetW + (blockSize * x) + blockSize,
                                  mapOffsetH + (blockSize * z) + blockSize);
                     }
                  }
               }
            }
         }

         set2Dcolour(black);
         draw2Dline(mapOffsetW - blockSize, mapOffsetH - blockSize, mapOffsetW + mapSize, mapOffsetH - blockSize, 5); // bottom
         draw2Dline(mapOffsetW - blockSize, mapOffsetH - blockSize, mapOffsetW - blockSize, mapOffsetH + mapSize, 5); // left
         draw2Dline(mapOffsetW + mapSize, mapOffsetH - blockSize, mapOffsetW + mapSize, mapOffsetH + mapSize, 5);     // right
         draw2Dline(mapOffsetW - blockSize, mapOffsetH + mapSize, mapOffsetW + mapSize, mapOffsetH + mapSize, 5);     // top

         //! @todo draw line around mapq
      }
      else if (displayMap == 2)
      {
         int mapSize = ((screenWidth / MAP_LARGE_SCALE) / WORLDX) * WORLDX;
         int blockSize = mapSize / WORLDX; // take the mapsize divided by the number of drawn blocks
         int buffer = (mapSize / MAP_LARGE_BUFFER);
         // int mapOffsetW = screenWidth - (buffer * 2) - mapSize;
         // int mapOffsetH = screenHeight - (buffer / 2) - mapSize;
         int mapOffsetW = (screenWidth - mapSize) / 2;
         int mapOffsetH = (screenHeight - mapSize) / 2;

         // draw viewpoint
         float vpX, vpY, vpZ = 0.0;
         getViewPosition(&vpX, &vpY, &vpZ);
         vpX *= -1.0;
         vpZ *= -1.0;
         set2Dcolour(white);
         draw2Dbox(mapOffsetW + (blockSize * (int)vpX),
                   mapOffsetH + (blockSize * (int)vpZ),
                   mapOffsetW + (blockSize * (int)vpX) + blockSize,
                   mapOffsetH + (blockSize * (int)vpZ) + blockSize);

         // draw world
         for (int y = WORLDY - 2; y >= 0; y--) // minus 2 to ensure we don't check out of array bounds
         {
            for (int x = 0; x < WORLDX - 1; x++)
            {
               for (int z = 0; z < WORLDZ - 1; z++)
               {
                  if (world[x][y][z] != 0 && y != CLOUD_LEVEL)
                  {
                     if (world[x][y + 1][z] == 0)
                     {
                        GLfloat ambRed, ambGreen, ambBlue, ambAlpha, difRed, difGreen, difBlue, difAlpha;
                        getUserColour(world[x][y][z], &ambRed, &ambGreen, &ambBlue, &ambAlpha, &difRed, &difGreen, &difBlue, &difAlpha);
                        float colour[4] = {ambRed, ambGreen, ambBlue, ambAlpha};
                        set2Dcolour(colour);
                        draw2Dbox(mapOffsetW + (blockSize * x),
                                  mapOffsetH + (blockSize * z),
                                  mapOffsetW + (blockSize * x) + blockSize,
                                  mapOffsetH + (blockSize * z) + blockSize);
                     }
                  }
               }
            }
         }

         set2Dcolour(black);
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH - (blockSize / 3), mapOffsetW + mapSize - (blockSize / 3), mapOffsetH - (blockSize / 3), 15);                     // bottom
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH - (blockSize / 3), mapOffsetW - (blockSize / 3), mapOffsetH + mapSize - (blockSize / 3), 15);                     // left
         draw2Dline(mapOffsetW + mapSize - (blockSize / 2), mapOffsetH - (blockSize / 3), mapOffsetW + mapSize - (blockSize / 2), mapOffsetH + mapSize - (blockSize / 3), 15); // right
         draw2Dline(mapOffsetW - (blockSize / 3), mapOffsetH + mapSize - (blockSize / 2), mapOffsetW + mapSize - (blockSize / 3), mapOffsetH + mapSize - (blockSize / 2), 15); // top
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
      static double cloudTime, projTime = 0.0;
      static double meteorTime = METEOR_SPAWN_TIME;
      struct timeval tv;
      gettimeofday(&tv, NULL);

      double curTime = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

      // cloud movement
      if (curTime - cloudTime >= CLOUD_SPEED)
      {
         cloudTime = curTime;

         for (int i = 0; i < g_clouds->numObj; i++)
         {
            Object *o = g_clouds->object[i];
            Cloud *c = o->ptr;
            int oldX = moveCloud(c, 1);
            world[oldX][c->y][c->z] = getColour(EMPTY);
            generateCloud(c);
         }
      }

      // projectile movement and collision
      if (curTime - projTime >= PROJECTILE_SPEED)
      {
         projTime = curTime;

         moveProjectile();
      }

      // generate new meteors
      if (curTime - meteorTime >= METEOR_SPAWN_TIME)
      {
         meteorTime = curTime;

         for (int i = 0; i < METEOR_PER_SPAWN; i++)
         {
            Meteor *m = createMeteor();
            initMeteor(m);
            addItem(g_meteors, m);
         }
      }

      // generate new meteors
      for (int i = 0; i < getListSize(g_meteors); i++)
      {
         Meteor *m = getItemAtIndex(g_meteors, i);
         if (curTime - m->timeTracker >= m->velocity)
         {
            m->timeTracker = curTime;
            if (m->isFalling)
            {
               moveMeteor(m);
            }
         }
      }
   }
}

/* called by GLUT when a mouse button is pressed or released */
/* -button indicates which button was pressed or released */
/* -state indicates a button down or button up event */
/* -x,y are the screen coordinates when the mouse is pressed or */
/*  released */
void mouse(int button, int state, int x, int y)
{

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      fireProjectile();
   }

   // if (button == GLUT_LEFT_BUTTON)
   //    printf("left button - ");
   // else if (button == GLUT_MIDDLE_BUTTON)
   //    printf("middle button - ");
   // else
   //    printf("right button - ");

   // if (state == GLUT_UP)
   // {
   //    printf("up - ");
   // }
   // else
   // {
   //    printf("down - ");
   // }

   // printf("%d %d\n", x, y);
}

int main(int argc, char **argv)
{
   /* Intializes random number generator */
   time_t t;
   srand((unsigned)time(&t));

   // initialize the graphics system
   graphicsInit(&argc, argv);

   // initialize world to empty
   initWorld();

   // initialize global tracking values
   g_num_mobs = 0;

   // initialize worlds game objects storage
   g_structures = createObjectStore(MAX_OBJECTS);
   g_clouds = createObjectStore(MAX_CLOUDS);
   g_projectile = createProjectile();
   g_meteors = createList();

   // create user defined colours
   createUserColours();

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
   free(g_projectile);

   return 0;
}
