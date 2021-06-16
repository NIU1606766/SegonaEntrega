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

// Inicialitzem totes les variables de la partida
ScrabbleGame::ScrabbleGame() : m_buttonSend(IMAGE_BUTTON_SEND_NORMAL, IMAGE_BUTTON_SEND_PRESSED, SCREEN_SIZE_X * 0.5 - 139 * 0.5, SCREEN_SIZE_Y - 100, 139, 100),
							   m_buttonShuffle(IMAGE_BUTTON_SHUFFLE_NORMAL, IMAGE_BUTTON_SHUFFLE_PRESSED, 440, SCREEN_SIZE_Y - 100, 100, 100),
							   m_buttonRecall(IMAGE_BUTTON_RECALL_NORMAL, IMAGE_BUTTON_RECALL_PRESSED, 200, SCREEN_SIZE_Y - 100, 100, 100),
							   m_buttonPass(IMAGE_BUTTON_PASS_NORMAL, IMAGE_BUTTON_PASS_PRESSED, SCREEN_SIZE_X * 0.5 - 139 * 0.5, SCREEN_SIZE_Y - 100, 139, 100),
							   m_board(),
							   m_currentPlayer(0),
							   m_lettersBag(),
							   m_nPasses(0),
							   m_gameOver(false)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		m_players[i].setPlayerScore(0);

		for (int j = 0; j < MAX_TILES; j++)
		{
			m_players[i].addTiles(m_lettersBag); // Donem les primeres fitxes a cada jugador
		}
	}
}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{	
	bool send = false;
	bool shuffle = false;
	bool recall = false;
	bool pass = false;
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0); // Dibuixem el fons i el tauler
	m_board.render();

	// Comencem els updates de player i els botons, i el checkBoard
	m_players[m_currentPlayer].update(mousePosX, mousePosY, mouseStatus, m_board);
	m_players[m_currentPlayer].checkBoard(m_board);


	if (m_players[m_currentPlayer].anyTileOnTheBoard()) {
		send = m_buttonSend.update(mousePosX, mousePosY, mouseStatus);
	} else {
		pass = m_buttonPass.update(mousePosX, mousePosY, mouseStatus); // Si no s'ha posat cap fitxa enlloc de send apareix el botó pass
	}
	shuffle = m_buttonShuffle.update(mousePosX, mousePosY, mouseStatus);
	recall = m_buttonRecall.update(mousePosX, mousePosY, mouseStatus);

	if (send && !m_gameOver) // Quan s'ha acabat la partida, els botons deixen de funcionar
	{
		bool result = m_players[m_currentPlayer].sendCurrentWordToBoard(m_board); // Executem el send amb el mètode "sendCurrentWordToBoard" de la classe Player (no confondre amb el de la classe Board)
		if (result) {
			// Agafem fitxes
			m_players[m_currentPlayer].addTiles(m_lettersBag);
			if (m_players[m_currentPlayer].noTiles()) // Si un jugador no té fitxes i no n'ha pogut agafar de la bossa
			{
				// S'ha acabat la partida
				m_gameOver = true;
			}
			// Passem de jugador
			m_currentPlayer++;
			if (m_currentPlayer >= NUM_PLAYERS) m_currentPlayer = 0;
			m_nPasses = 0;
		}
	}

	if (shuffle && !m_gameOver)
	{
		m_players[m_currentPlayer].recall(); // Abans de barrejar les fitxes les tornem a la mà del jugador amb el mètode recall
		m_board.removeCurrentWord();
		m_players[m_currentPlayer].shuffle();
	}

	if(recall && !m_gameOver)
	{
		m_players[m_currentPlayer].recall();
		m_board.removeCurrentWord();
	}

	if (pass && !m_gameOver)
	{
		// Passem de jugador
		m_currentPlayer++;
		if (m_currentPlayer >= NUM_PLAYERS) m_currentPlayer = 0; // Per anar rotant de jugadors, quan arribem al final de l'array de jugadors tornem al principi
		m_nPasses++;
		if (m_nPasses > NUM_PLAYERS) // Per comprovar que cap jugador pugui tirar, esperem a que tots ells apretin el botó pass
		{
			cout << "Game over\n"; // S'ha acabat la partida
			m_gameOver = true;
		}
	}

	// Fem el render dels botons
	m_buttonRecall.render();
	m_buttonShuffle.render();
	if (m_players[m_currentPlayer].anyTileOnTheBoard())
	{
		m_buttonSend.render();
	}
	else // Si no s'ha posat cap fitxa, apareix el botó pass enlloc del send
	{
		m_buttonPass.render();
	}

	// Representar la puntuació de cada jugador
	string points1 = "Player 1 Score: " + to_string(m_players[0].getPlayerScore());
	string points2 = "Player 2 Score: " + to_string(m_players[1].getPlayerScore());
	string points3 = "Player 3 Score: " + to_string(m_players[2].getPlayerScore());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 750, 0.6, points1);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 775, 0.6, points2);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 800, 0.6, points3);

	// Representar de qui és el torn actual
	string turn = "Player turn: " + to_string(m_currentPlayer + 1);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 6, 5, 0.6, turn);

	// Representar les fitxes que queden a la bossa
	string bagLetters = "Tiles in the bag: " + to_string(m_lettersBag.getLettersQuantity());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 550, 750, 0.6, bagLetters);
    
	// Game over
	string fin = "GAME OVER";
	if (m_gameOver)
	{
		GraphicManager::getInstance()->drawFont(FONT_RED_30, 550, 0, 1, fin);
	}

}
