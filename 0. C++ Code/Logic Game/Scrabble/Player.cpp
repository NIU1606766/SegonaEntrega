#include "Player.h"
#include "../GraphicManager.h"
#include <iostream>
#include <stdlib.h>

void Player::update(int mousePosX, int mousePosY, bool mouseStatus, Board& board)
{
	float cellSize = (BOARD_SIZE / BOARD_COLS_AND_ROWS);
	// Comprovar si vol arrastrar fitxa
	for (int i = 0; i < MAX_TILES; i++)
	{
		float cellSize_i = cellSize;
		if (!m_tiles[i].getIsOnBoard()) {
			cellSize_i = 100;
		}
		if ((mousePosX >= m_tiles[i].getPosX() && mousePosX <= m_tiles[i].getPosX() + cellSize_i) &&
			(mousePosY >= m_tiles[i].getPosY() && mousePosY <= m_tiles[i].getPosY() + cellSize_i) &&
			mouseStatus && !m_isDragging)
		{
			m_tiles[i].setSizeSmall(true);
			if (m_tiles[i].getIsOnBoard()) {

				std::cout << "traient de la posicio vella" << std::endl;
				board.removeTile(m_tiles[i].getBoardPosition()); //el traiem de la posició vella
				m_tiles[i].setIsOnBoard(false);
			}
			m_isDragging = true;
			m_tileDragging = i;
		}

	}

	// Establir posicio de cada fitxa
	int j = 0;
	for (int i = 0; i < MAX_TILES; i++)
	{
		// Si estan al atril (no arrastrant i no al board)
		if ((!m_isDragging && !m_tiles[i].getIsOnBoard()))
		{
			m_tiles[i].setPos(PLAYER_TILE_POS_X + j, PLAYER_TILE_POS_Y);
			m_tiles[m_tileDragging].setSizeSmall(false);
		}
		j += 107;
	}

	// Print lletra a la posició establerta
	j = 0;
	for (int i = 0; i < MAX_TILES; i++) 
	{
		if (!m_tiles[i].getIsEmpty()) {
			m_tiles[i].printLetter();
		}
		j += 105;
	}

	//IF ARRASTRANT
	if (m_isDragging) { //s'esta arrastrant per la partida?
		m_tiles[m_tileDragging].setPos(mousePosX, mousePosY);
		if (!mouseStatus) //està arrestrant pero ha deixat anar el boto?
		{
			m_isDragging = false;
			PositionResult result;
			int col = int((mousePosX - BOARD_POS_X) / cellSize);
			int row = int((mousePosY - BOARD_POS_Y) / cellSize);
			BoardPosition boardPos(col, row);
			//int colDef, rowDef;
			if (mousePosX < BOARD_POS_X || mousePosX > BOARD_POS_X + BOARD_SIZE ||
				mousePosY < BOARD_POS_Y || mousePosY > BOARD_POS_Y + BOARD_SIZE || !board.getCell(row, col).getEmpty()) 
			{ 
				//fora del taulell a les X o les Y
				result = INVALID_POSITION;
				m_tiles[m_tileDragging].setIsOnBoard(false);
			}
			else {
				result = board.setTile(m_tiles[m_tileDragging].getTile(), boardPos); //intenta posar la lletra al tauler
				m_tiles[m_tileDragging].setBoardPosition(boardPos);
				cout << "PARAULA SETTILE: " << m_tiles[m_tileDragging].getTile().getLetter() << endl;

				if (result == VALID_POSITION) {
					float posY = boardPos.getRow() * cellSize + BOARD_POS_Y;
					float posX = boardPos.getCol() * cellSize + BOARD_POS_X;
					m_tiles[m_tileDragging].setPos(posX, posY);
				}
			}
			switch (result) {
			case INVALID_POSITION:
				m_tiles[m_tileDragging].setSizeSmall(false);
				m_tiles[m_tileDragging].setIsOnBoard(false); //isOnBoard = false --> pickupFromBoard()
				m_allCorrect = false;
				std::cout << "INVALID POSITION" << std::endl;
				break;
			case NOT_EMPTY:
				m_tiles[m_tileDragging].setSizeSmall(false);
				m_tiles[m_tileDragging].setIsOnBoard(false);
				std::cout << "NOT EMPTY CELL" << std::endl;
				break;
			case VALID_POSITION:
				m_tiles[m_tileDragging].setSizeSmall(true);
				m_tiles[m_tileDragging].setIsOnBoard(true); //isOnBoard = true --> leaveOnBoard()
				std::cout << "VALID POSITION" << std::endl;
				break;
			default:
				break;
			}
		}
	}
}

void Player::render(int mousePosX, int mousePosY, bool mouseStatus)
{
	
}

void Player::addTiles(LettersBag& lb)
{
	//FALTA PRINTAR LA NOVA LLETRA EN AQUEST MÈTODE?

		for (int i = 0; i < MAX_TILES; i++) {
			if (m_tiles[i].getIsEmpty()) //la lletra ha estat jugada i validada per tant fa falta afegir una nova de la bag (o es el primer torn i totes les pos estan buides)
			{
				m_tiles[i].setTile(lb.getLetter()); //omplo la posició
				m_tiles[i].setSizeSmall(false);
				m_tiles[i].setIsEmpty(false); //dic que la posicio ja no esta buida
			}
		}
}

bool Player::sendCurrentWordToBoard(Board& board)
{
	if (board.checkCurrentWord(m_score) == ALL_CORRECT) {
		for (int i = 0; i < MAX_TILES; i++) { //comprovo si s'han tirat totes les fitxes (pendents de validar)
			if (m_tiles[i].getIsOnBoard()) {
				//m_boardTiles.push_back(m_tiles[i].getTile()); //guardo la fitxa jugada per poder sobreescriure la posicio al atril al setTile

				//m_boardTilesPosition.push_back(make_pair(m_tiles[i].getPosX(), m_tiles[i].getPosY()));

				// resetegem el playertile
				m_tiles[i].setSizeSmall(false);
				m_tiles[i].setPos(PLAYER_TILE_POS_X + i + 105 * i, PLAYER_TILE_POS_Y);
				//m_allCorrect = true;

				m_tiles[i].setIsEmpty(true);
				m_tiles[i].setIsOnBoard(false);

			}

		}
		board.sendCurrentWordToBoard();
		m_allCorrect = true;

		return true;
	}
	return false;
}

bool Player::anyTileOnTheBoard()
{
	bool anyTile = false;

	for (int i = 0; i < MAX_TILES; i++)
	{
		// Comprovo si hi ha alguna fitxa jugada a la board (pendent de validar)
		if (m_tiles[i].getIsOnBoard())
		{
			anyTile = true;
			m_allCorrect = false;
		}
	}

	return anyTile;
}

bool Player::allTilesPlayed()
{
	bool allTiles = true;

	for (int i = 0; i < MAX_TILES; i++)
	{
		// Comprovo si s'han tirat totes les fitxes (pendents de validar)
		if (!m_tiles[i].getIsOnBoard())
			allTiles = false;
	}

	return allTiles;
}

IMAGE_NAME Player::imageSmall2(char letter)
{
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
	// Lletres del board

	for (int i = 0; i < m_boardTiles.size(); i++)
	{
		IMAGE_NAME img = imageSmall2(m_boardTiles[i].getLetter());
		float posX = m_boardTilesPosition[i].first;
		float posY = m_boardTilesPosition[i].second;
		GraphicManager::getInstance()->drawSprite((IMAGE_NAME)img, posX, posY);
	}
}

void Player::recall()
{
	// Recorrer tota la matriu i recollir fitxes jugant-se actualment (tornar a pintar tot però sense les lletres jugant-se)
	int posX = BOARD_POS_X;
	int posY = BOARD_POS_Y;

	for (int i = 0; i < MAX_TILES; i++)
	{
		if (m_tiles[i].getIsOnBoard())
		{
			m_tiles[i].setIsOnBoard(false);
		}
	}

	for (int i = 0; i < m_setTiles.size(); i++)
	{
		m_setTiles.pop_back();
	}
}

void Player::shuffle()
{
	PlayerTile aux;
	std::cout << "ordre inicial: ";
	for (int i = 0; i < MAX_TILES; i++) {
		cout << m_tiles[i].getTile().getLetter() << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < MAX_TILES; i++) {

		int pos = rand() % MAX_TILES;

		while (!m_tiles[pos].getIsOnBoard() && m_tiles[pos].getPosY() == PLAYER_TILE_POS_Y && pos == i)
			pos = rand() % MAX_TILES;

		if (!m_tiles[i].getIsOnBoard() && m_tiles[i].getPosY() == PLAYER_TILE_POS_Y)
		{
			aux = m_tiles[i];
			m_tiles[i] = m_tiles[pos];
			m_tiles[pos] = aux;
		}
	}

	std::cout << "ordre barrejat: ";
	for (int i = 0; i < MAX_TILES; i++) {
		std::cout << m_tiles[i].getTile().getLetter() << "  ";
	}
	std::cout << std::endl;

}