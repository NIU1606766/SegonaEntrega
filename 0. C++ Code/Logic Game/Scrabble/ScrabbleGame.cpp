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
							   m_buttonShuffle(IMAGE_BUTTON_SHUFFLE_NORMAL, IMAGE_BUTTON_SHUFFLE_PRESSED, 440, SCREEN_SIZE_Y - 100, 100, 100),
							   m_buttonRecall(IMAGE_BUTTON_RECALL_NORMAL, IMAGE_BUTTON_RECALL_PRESSED, 200, SCREEN_SIZE_Y - 100, 100, 100),
							   m_buttonPass(IMAGE_BUTTON_PASS_NORMAL, IMAGE_BUTTON_PASS_PRESSED, SCREEN_SIZE_X * 0.5 - 139 * 0.5, SCREEN_SIZE_Y - 100, 139, 100),
							   m_board(),
							   m_currentPlayer(0),
							   m_lettersBag()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		m_players[i].setPlayerScore(0);

		for (int j = 0; j < MAX_TILES; j++)
		{
			m_players[i].addTiles(m_lettersBag);
		}
	}
}

ScrabbleGame::~ScrabbleGame(){
    
}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{	
	bool send = false;
	bool shuffle = false;
	bool recall = false;
	bool pass = false;
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);
	m_board.render();
	m_players[m_currentPlayer].update(mousePosX, mousePosY, mouseStatus, m_board);

	//if (m_players[m_currentPlayer].anyTileOnTheBoard())
	//	m_players[m_currentPlayer].sendCurrentWordToBoard(m_board);

	m_players[m_currentPlayer].checkBoard(m_board);



	if (m_players[m_currentPlayer].anyTileOnTheBoard()) {
		send = m_buttonSend.update(mousePosX, mousePosY, mouseStatus);
	} else {
		pass = m_buttonPass.update(mousePosX, mousePosY, mouseStatus);
	}
	shuffle = m_buttonShuffle.update(mousePosX, mousePosY, mouseStatus);
	recall = m_buttonRecall.update(mousePosX, mousePosY, mouseStatus);

	if (send)
	{
		bool result = m_players[m_currentPlayer].sendCurrentWordToBoard(m_board);
		if (result) {
			// agafem fitxes
			m_players[m_currentPlayer].addTiles(m_lettersBag);
			// passem de jugador
			m_currentPlayer++;
			if (m_currentPlayer >= NUM_PLAYERS) m_currentPlayer = 0;
		}
	}

	if (shuffle)
	{
		m_players[m_currentPlayer].shuffle();
	}

	if(recall)
	{
		m_players[m_currentPlayer].recall();
	}

	if (pass)
	{
		// passem de jugador
		m_currentPlayer++;
		if (m_currentPlayer >= NUM_PLAYERS) m_currentPlayer = 0;
	}

	m_buttonRecall.render();
	m_buttonShuffle.render();
	if (m_players[m_currentPlayer].anyTileOnTheBoard()) {
		m_buttonSend.render();
	}
	else {
		m_buttonPass.render();
	}

	// Representar la puntuació de cada jugador
	string points1 = "Player 1 Score: " + to_string(m_players[0].getPlayerScore());
	string points2 = "Player 2 Score: " + to_string(m_players[1].getPlayerScore());
	string points3 = "Player 3 Score: " + to_string(m_players[2].getPlayerScore());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 750, 0.6, points1);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 775, 0.6, points2);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 800, 0.6, points3);


    
}
