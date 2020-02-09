/**
 * CIS4820 Game Programming - Winter 2020
 * @author Mark Sansome
 * 0916066
*/

#ifndef msansome_map_h
#define msansome_map_h

/**
 * draws the players viewpoint on the map in white
 * @param mapWidthOffset where to draw the map from screen width, screen bottom left
 * @param mapHeightOffset where to draw the map from screen height, screen bottom left
 * @param blockSize how large one map pixel (block) is in relation to the map size
 */
extern void mapDrawViewPosition(int mapWidthOffset, int mapHeightOffset, int blockSize);

/**
 * draws the world array on the map in each block colour
 * @param mapWidthOffset where to draw the map from screen width, screen bottom left
 * @param mapHeightOffset where to draw the map from screen height, screen bottom left
 * @param blockSize how large one map pixel (block) is in relation to the map size
 */
extern void mapDrawWorld(int mapWidthOffset, int mapHeightOffset, int blockSize);

#endif // msansome_map_h