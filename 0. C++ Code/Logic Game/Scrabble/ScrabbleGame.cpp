//
//  ScrabbleGame.cpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#include "ScrabbleGame.h"
#include "../Scrabble_Defs.h"

#include "../GraphicManager.h"

using std::string;

ScrabbleGame::ScrabbleGame()
{
	m_buttonPressed = false;
	m_drawLetter = false;
}

ScrabbleGame::~ScrabbleGame(){
    
}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{	
	int btn_size_w = 139;
	int btn_size_h = 100;
	int btn_pos_x = SCREEN_SIZE_X*0.5 - btn_size_w*0.5;
	int btn_pos_y = SCREEN_SIZE_Y - btn_size_h;
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);
	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, BOARD_POS_X, BOARD_POS_Y);
	
	
	if (mouseStatus && mousePosX >= btn_pos_x && mousePosY>=btn_pos_y && mousePosX<=btn_pos_x+btn_size_w && mousePosY <= btn_pos_y + btn_size_h)
	{
		GraphicManager::getInstance()->drawSprite(IMAGE_BUTTON_SEND_PRESSED, btn_pos_x, btn_pos_y);
		int posX = BOARD_POS_X;
		int posY = BOARD_POS_Y;
		for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
		{
			for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
			{
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_SMALL, posX, posY);
				posX += BOARD_TILE_SIZE;
			}
			posY += BOARD_TILE_SIZE;
			posX = BOARD_POS_X;
		}
	}
	else
	{
		GraphicManager::getInstance()->drawSprite(IMAGE_BUTTON_SEND_NORMAL, btn_pos_x, btn_pos_y);
	}
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 10, 10, 0.6, msg);
    
}
