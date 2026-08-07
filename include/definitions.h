#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/***************************************************************/
// Metadata
/***************************************************************/
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define FRAME_RATE 60
/***************************************************************/



/***************************************************************/
// Board data
/***************************************************************/
// Measured in blocks.
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define PREVIEW_PIECE_COUNT 5

#define OUTLINE_THICKNESS 1.5
#define BOARD_OUTLINE_THICKNESS 3
#define BLOCKSIZE 35 // Can have it relative sometime?
/***************************************************************/



/***************************************************************/
// Mino data
/***************************************************************/
#define I_MINO 1
#define O_MINO 2
#define T_MINO 3
#define L_MINO 4
#define J_MINO 5
#define S_MINO 6
#define Z_MINO 7

/***************************************************************/



/***************************************************************/
// Randomizer data
/***************************************************************/

#define REFRESH_BAG 0
#define BAG_SIZE 7
/***************************************************************/



/***************************************************************/
// Misc
/***************************************************************/
#define TRANSPARENT_WHITE (Color) {255, 255, 255, 100}
#define DARKPURPLE_TRANSPARENT (Color) {112, 31, 126, 100}
#define ORANGE_TRANSPARENT (Color) {255, 140, 0, 100}
#define DARKGRAY_TRANSPARENT (Color) {80, 80, 80, 100}
#define MAROON_TRANSPARENT (Color){190, 33, 55, 100}
#define BLUE_TRANSPARENT (Color){0, 121, 241, 100}

/***************************************************************/



/***************************************************************/
// Network data
/***************************************************************/
#define NET_MESSAGE_CHANNEL 0
#define NET_BOARD_CHANNEL 1

#endif