#include "Player.h"
#include "../GraphicManager.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>

void Player::update(int mousePosX, int mousePosY, bool mouseStatus, Board& board)
{

	float cellSize = (BOARD_SIZE / BOARD_COLS_AND_ROWS);


	// Hem de comprovar si vol arrastrar alguna fitxa del jugador. Primer recorrem tota la matriu de fitxes:
	for (int i = 0; i < MAX_TILES; i++)
	{
		float cellSize_i = cellSize;
		if (!m_tiles[i].getIsOnBoard()) {
			cellSize_i = 100;
		}
		// Mirem si el mouse ha estat apretat mentre la fitxa era a la mà, i per tant ha de fer-se petita.
		if ((mousePosX >= m_tiles[i].getPosX() && mousePosX <= m_tiles[i].getPosX() + cellSize_i) && (mousePosY >= m_tiles[i].getPosY() && mousePosY <= m_tiles[i].getPosY() + cellSize_i) && mouseStatus && !m_isDragging)
		{
			m_tiles[i].setSizeSmall(true);

			// Si la fitxa ja estava al tauler, la traiem d'aquest.
			if (m_tiles[i].getIsOnBoard()) {

				board.removeTile(m_tiles[i].getBoardPosition());
				m_tiles[i].setIsOnBoard(false);
			}

			// Posem el booleà de que s'està arrastrant a true, i diem que l'índex de la fitxa és i.
			m_isDragging = true;
			m_tileDragging = i;
		}

	}

	// Establim la posició de cada fitxa
	int j = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		//Si no s'estan movent ni estan al tauler, es que estan en repos a la mà
		if ((!m_isDragging && m_tiles[i].getIsOnBoard() == false))
		{
			// Les assignem a la posició (4+107i,645) que és la posició de la mà, i les posem en gran.
			m_tiles[i].setPos(PLAYER_TILE_POS_X + j, PLAYER_TILE_POS_Y);
			m_tiles[m_tileDragging].setSizeSmall(false);
		}
		j += 107;
	}

	
	j = 0;
	for (int i = 0; i < MAX_TILES; i++) 
	{
		// Recorrem totes les tiles del jugador i les renderitzem a pantalla.
		if (!m_tiles[i].getIsEmpty()) {
			m_tiles[i].printLetter();
		}
		j += 105;
	}

	// Si estem movent una fitxa: 
	if (m_isDragging) {

		// Actualitzem la seva posició a la del mouse
		m_tiles[m_tileDragging].setPos(mousePosX, mousePosY);

		//Si deixa d'apretar el botó, comprovarem si la fitxa està posada en un lloc del tauell o no.
		if (!mouseStatus)
		{
			m_isDragging = false;
			PositionResult result;
			int col = int((mousePosX - BOARD_POS_X) / cellSize);
			int row = int((mousePosY - BOARD_POS_Y) / cellSize);
			BoardPosition boardPos(col, row);


			// Si està fora de les coordenades del tauler, retorna invalid position, i no la deixem al taulell, evidentment.
			if (mousePosX < BOARD_POS_X || mousePosX > BOARD_POS_X + BOARD_SIZE ||
				mousePosY < BOARD_POS_Y || mousePosY > BOARD_POS_Y + BOARD_SIZE || !board.getCell(row, col).getEmpty()) 
			{ 
				
				result = INVALID_POSITION;
				m_tiles[m_tileDragging].setIsOnBoard(false);
			}
			else 
			{
				result = board.setTile(m_tiles[m_tileDragging].getTile(), boardPos); 
				m_tiles[m_tileDragging].setBoardPosition(boardPos);
				
				// Si el resultat és vàlid passem de les posicions del ratolí a la cel·la del tauler i deixem la fitxa allà.
				if (result == VALID_POSITION) {
					float posY = boardPos.getRow() * cellSize + BOARD_POS_Y;
					float posX = boardPos.getCol() * cellSize + BOARD_POS_X;
					m_tiles[m_tileDragging].setPos(posX, posY);
				}
			}
			switch (result) 
			{
				// Si és posició no vàlida, marquem que el tamany és gran i no la deixem al tauler.
				case INVALID_POSITION:
					m_tiles[m_tileDragging].setSizeSmall(false);
					m_tiles[m_tileDragging].setIsOnBoard(false);
					m_allCorrect = false;
					break;

				// Si és posició no és buida, marquem que el tamany és gran i no la deixem al tauler.
				case NOT_EMPTY:
					m_tiles[m_tileDragging].setSizeSmall(false);
					m_tiles[m_tileDragging].setIsOnBoard(false);
					break;

				// Si la posició és correcta, la posem en petit i la deixem al tauler.
				case VALID_POSITION:
					m_tiles[m_tileDragging].setSizeSmall(true);
					m_tiles[m_tileDragging].setIsOnBoard(true);
					break;

				default:
					break;
			}
		}
	}
}


void Player::addTiles(LettersBag& lb)
{

		// Recorrem totes les tiles del jugador:
		for (int i = 0; i < MAX_TILES; i++) {
			
			// Si la tile està buida, vol dir que ja ha estat jugada i cal repostar la mà amb fitxes noves.
			if (m_tiles[i].getIsEmpty())
			{
				// Mentre la LetterBag segueixi tenint fitxes, omplim la posició buida amb una nova d'aquesta.
				if (lb.getLettersBagSize() > 0)
				{
					m_tiles[i].setTile(lb.getLetter());
					m_tiles[i].setSizeSmall(false);
					m_tiles[i].setIsEmpty(false);
				}
				else
				{
					lb.setEmpty(true);
				}
			}
		}
}

bool Player::sendCurrentWordToBoard(Board& board)
{
	// Si la paraula del board resulta correcta:
	if (board.checkCurrentWord(m_score) == ALL_CORRECT) 
	{
		// Recorrem totes les fitxes del jugador:
		for (int i = 0; i < MAX_TILES; i++) 
		{
			// Si la tile està al tauler:
			if (m_tiles[i].getIsOnBoard()) 
			{
				// resetegem el playertile
				m_tiles[i].setSizeSmall(false);
				m_tiles[i].setPos(PLAYER_TILE_POS_X + i + 107 * i, PLAYER_TILE_POS_Y);
				m_tiles[i].setIsEmpty(true);
				m_tiles[i].setIsOnBoard(false);

			}
		}
		// Enviem la paraula al board i posem m_allCorrect a true.
		board.sendCurrentWordToBoard();
		m_allCorrect = true;

		return true;
	}
	return false;
}

bool Player::tilesOnBoard()
{
	bool boardTile = false;

	// Fem un for per recorrer totes les tiles i veure si n'hi ha alguna al tauler.
	for (int i = 0; i < MAX_TILES; i++)
	{
		// Si hi ha alguna al tauler, boardTile = true, i allCorrect = false.
		if (m_tiles[i].getIsOnBoard())
		{
			boardTile = true;
			m_allCorrect = false;
		}
	}

	return boardTile;
}

bool Player::everyTilePlayed()
{
	bool everyTilePlayed = true;

	// Fem un for per recorrer totes les tiles del jugador i comprovar si estan al tauler o no.
	for (int i = 0; i < MAX_TILES; i++)
	{
		// Si n'hi ha alguna que no estigui al tauler, voldrà dir que no s'han jugat totes, i per tant, everyTilePlayed = false.
		if (!m_tiles[i].getIsOnBoard())
			everyTilePlayed = false;
	}

	return everyTilePlayed;
}

IMAGE_NAME Player::imageSmall(char letter)
{
	// Aquesta funció el que fa és retornar l'imagename corresponent a la lletra que li passem per paràmetre, en petit.
	switch (letter)
	{
	case 'a':
		return IMAGE_LETTER_A_SMALL;
		break;

	case 'b':
		return IMAGE_LETTER_B_SMALL;
		break;

	case 'c':
		return IMAGE_LETTER_C_SMALL;
		break;

	case 'd':
		return IMAGE_LETTER_D_SMALL;
		break;

	case 'e':
		return IMAGE_LETTER_E_SMALL;
		break;

	case 'f':
		return IMAGE_LETTER_F_SMALL;
		break;

	case 'g':
		return IMAGE_LETTER_G_SMALL;
		break;

	case 'h':
		return IMAGE_LETTER_H_SMALL;
		break;

	case 'i':
		return IMAGE_LETTER_I_SMALL;
		break;

	case 'j':
		return IMAGE_LETTER_J_SMALL;
		break;

	case 'k':
		return IMAGE_LETTER_K_SMALL;
		break;

	case 'l':
		return IMAGE_LETTER_L_SMALL;
		break;

	case 'm':
		return IMAGE_LETTER_M_SMALL;
		break;

	case 'n':
		return IMAGE_LETTER_N_SMALL;
		break;

	case 'o':
		return IMAGE_LETTER_O_SMALL;
		break;

	case 'p':
		return IMAGE_LETTER_P_SMALL;
		break;

	case 'q':
		return IMAGE_LETTER_Q_SMALL;
		break;

	case 'r':
		return IMAGE_LETTER_R_SMALL;
		break;

	case 's':
		return IMAGE_LETTER_S_SMALL;
		break;

	case 't':
		return IMAGE_LETTER_T_SMALL;
		break;

	case 'u':
		return IMAGE_LETTER_U_SMALL;
		break;

	case 'v':
		return IMAGE_LETTER_V_SMALL;
		break;

	case 'w':
		return IMAGE_LETTER_W_SMALL;
		break;

	case 'x':
		return IMAGE_LETTER_X_SMALL;
		break;

	case 'y':
		return IMAGE_LETTER_Y_SMALL;
		break;

	case 'z':
		return IMAGE_LETTER_Z_SMALL;
		break;

	default:
		break;
	}
}

void Player::checkBoard(Board& board)
{
	// Recorrem el vector de tiles al board:
	for (int i = 0; i < m_boardTiles.size(); i++)
	{
		// Posem la imatge petita de la lletra que li toqui, i la renderitzem a les posicions que li toquen.
		IMAGE_NAME img = imageSmall(m_boardTiles[i].getLetter());
		float posX = m_boardTilesPosition[i].first;
		float posY = m_boardTilesPosition[i].second;
		GraphicManager::getInstance()->drawSprite((IMAGE_NAME)img, posX, posY);
	}
}

void Player::recall()
{
	int posX = BOARD_POS_X;
	int posY = BOARD_POS_Y;

	// Recorrem totes les tiles del player per mirar quines estan al board i retornarles a la mà
	for (int i = 0; i < MAX_TILES; i++)
	{
		if (m_tiles[i].getIsOnBoard())
		{
			m_tiles[i].setIsOnBoard(false);
		}
	}

	// Tornem a fer un for per recorrer el vector de setTiles i els traiem tots perquè al fer recall, es treuen totes les fitxes del torn.
	for (int i = 0; i < m_setTiles.size(); i++)
	{
		m_setTiles.pop_back();
	}
}

void Player::shuffle()
{
	PlayerTile aux;

	// Recorrem totes les tiles del jugador:
	for (int i = 0; i < MAX_TILES; i++) {

		// Guardem en una variable un nombre random.
		int pos = rand() % MAX_TILES;

		// Si la tile en i no està al tauler i tampoc la de l'índex random, les canviem de lloc.
		if (!m_tiles[i].getIsOnBoard() && !m_tiles[pos].getIsOnBoard())
		{
			aux = m_tiles[i];
			m_tiles[i] = m_tiles[pos];
			m_tiles[pos] = aux;
		}
	}

}

bool Player::noTiles()
{
	// Recorrem totes les tiles del jugador:
	for (int i = 0; i < MAX_TILES; i++)
	{
		// Si alguna tile no està buida, retorna false, perquè encara queden tiles.
		if (!m_tiles[i].getIsEmpty())
		{
			return false;
		}
	}
	return true;
}