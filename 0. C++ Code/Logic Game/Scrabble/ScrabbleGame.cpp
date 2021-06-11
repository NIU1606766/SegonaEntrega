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
			m_players[i].setPlayerTile(m_lettersBag.getLetter());
		}
	}
}

ScrabbleGame::~ScrabbleGame(){
    
}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{	
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);
	m_board.render();
	m_players[m_currentPlayer].update(mousePosX, mousePosY, mouseStatus, m_board);
	//m_players[m_currentPlayer].render(mousePosX, mousePosY, mouseStatus);
	bool recall = m_buttonRecall.update(mousePosX, mousePosY, mouseStatus);
	bool shuffle = m_buttonShuffle.update(mousePosX, mousePosY, mouseStatus);
	bool send = m_buttonSend.update(mousePosX, mousePosY, mouseStatus);
	bool pass = m_buttonPass.update(mousePosX, mousePosY, mouseStatus);

	if (send)
	{
		CurrentWordResult result;
		int score = m_players[m_currentPlayer].getPlayerScore();
		result = m_board.checkCurrentWord(score);
		string msg;
		

		if (result == ALL_CORRECT)
		{
			m_board.sendCurrentWordToBoard();
			m_players[m_currentPlayer].setPlayerScore(score);
			msg = "Score: " + to_string(score);
			GraphicManager::getInstance()->drawFont(FONT_GREEN_30, 200, 10, 0.6, msg);
		}
		else
		{
			switch (result)
			{
				case INVALID_NOT_ALIGNED:
					msg = "Les fitxes han d'estar alineades i consecutives.";
					GraphicManager::getInstance()->drawFont(FONT_RED_30, 200, 10, 0.6, msg);
					break;

				case INVALID_NOT_CONNECTION:
					msg = "La paraula actual ha d'estar tocant fitxes de torns anteriors.";
					GraphicManager::getInstance()->drawFont(FONT_RED_30, 200, 10, 0.6, msg);
					break;

				case INVALID_START_NOT_IN_CENTER:
					msg = "Al 1r torn cal col·locar una fitxa a la posició central del tauler.";
					GraphicManager::getInstance()->drawFont(FONT_RED_30, 200, 10, 0.6, msg);
					break;

				case INVALID_WORD_OF_ONE_LETTER:
					msg = "Les paraules d'una sola lletra no són vàlides.";
					GraphicManager::getInstance()->drawFont(FONT_RED_30, 200, 10, 0.6, msg);
					break;

				case INVALID_WORDS_NOT_IN_DICTIONARY:
					msg = "Alguna paraula no apareix al diccionari.";
					GraphicManager::getInstance()->drawFont(FONT_RED_30, 200, 10, 0.6, msg);
					break;

				default:
					break;
			}
		}
	}

	if (shuffle)
	{
		m_board.removeCurrentWord();
		// Treure fitxes del tauler i retornar-les al jugador
	}

	if (recall)
	{

	}

	if (pass)
	{
		if (m_currentPlayer == 0)
			m_currentPlayer = 1;

		if (m_currentPlayer == 1)
			m_currentPlayer = 2;

		if (m_currentPlayer == 2)
			m_currentPlayer = 0;
	}
	
	
	m_buttonSend.render();
	m_buttonShuffle.render();
	m_buttonRecall.render();
	// m_buttonPass.render();
	string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 10, 10, 0.6, msg);

	// Representar la puntuació de cada jugador
	string points1 = "Player 1 Score: " + to_string(m_players[0].getPlayerScore());
	string points2 = "Player 2 Score: " + to_string(m_players[1].getPlayerScore());
	string points3 = "Player 3 Score: " + to_string(m_players[2].getPlayerScore());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 750, 0.6, points1);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 775, 0.6, points2);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 800, 0.6, points3);


    
}
