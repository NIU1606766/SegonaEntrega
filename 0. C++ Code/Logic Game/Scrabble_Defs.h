//
//  Scrabble.h
//  MP_Practica
//
//  Created by Enric Vergara on 14/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef Scrabble_Defs_h
#define Scrabble_Defs_h


// Screen size (W,H)=(750,850)
const int SCREEN_SIZE_X			= 750; 
const int SCREEN_SIZE_Y			= 850; 
const int BOARD_SIZE			= 600;
const int BOARD_COLS_AND_ROWS   = 15;
const int BOARD_TILE_SIZE       = BOARD_SIZE / BOARD_COLS_AND_ROWS;


//TODO 1.4
/*---Codi a fer:
const int BOARD_POS_X = SCREEN_SIZE_X * 0.5 - BOARD_SIZE * 0.5;
const int BOARD_POS_Y = 40;
*/

const int BOARD_POS_X = SCREEN_SIZE_X * 0.5 - BOARD_SIZE * 0.5;
const int BOARD_POS_Y = 40;


const int MAX_TILES = 7;
const int NUM_PLAYERS = 3;

const int PLAYER_TILE_POS_X = 4;
const int PLAYER_TILE_POS_Y = 645;

#endif /* Scrabble_Defs_h */
