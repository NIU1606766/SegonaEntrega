//
//  ScrabbleGame.cpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#include "ScrabbleGame.h"
#include "../Scrabble_Defs.h"

using std::string;

ScrabbleGame::ScrabbleGame() : m_buttonSend(IMAGE_BUTTON_SEND_NORMAL, IMAGE_BUTTON_SEND_PRESSED, SCREEN_SIZE_X * 0.5 - 139 * 0.5, SCREEN_SIZE_Y - 100, 139, 100),
							   m_buttonShuffle(IMAGE_BUTTON_SHUFFLE_NORMAL, IMAGE_BUTTON_SHUFFLE_PRESSED, 440, SCREEN_SIZE_Y - 100, 139, 100),
							   m_buttonRecall(IMAGE_BUTTON_RECALL_NORMAL, IMAGE_BUTTON_RECALL_PRESSED, 200, SCREEN_SIZE_Y -100, 139, 100)
{
}

ScrabbleGame::~ScrabbleGame(){
    
}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{	
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);
	m_board.render();

	
	bool pressed = m_buttonSend.update(mousePosX, mousePosY, mouseStatus);
	if (pressed)
	{
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
	m_buttonSend.render();
	m_buttonShuffle.render();
	m_buttonRecall.render();
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 10, 10, 0.6, msg);


    
}
