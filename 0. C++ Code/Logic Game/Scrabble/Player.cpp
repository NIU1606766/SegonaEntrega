#include "Player.h"
#include "../GraphicManager.h"
#include <iostream>


void Player::setPlayerTile(Tile tile)
{
	bool trobat = false;

	for (int i = 0; i < MAX_TILES && !trobat; i++)
	{
		if (m_tiles[i].getIsEmpty() == true)
		{
			m_tiles[i].setTile(tile);
			m_tiles[i].setIsEmpty(false);
			m_tiles[i].setIsOnBoard(false);
			m_tiles[i].setSizeSmall(false);
			trobat = true;
		}
	}
}
void Player::update(int mousePosX, int mousePosY, bool mouseStatus, Board& board)
{

	// Comprovar si vol arrastrar fitxa
	for (int i = 0; i < MAX_TILES; i++)
	{
		if ((mousePosX >= m_tiles[i].getPosX() && mousePosX <= m_tiles[i].getPosX() + 100) && 
			(mousePosY >= m_tiles[i].getPosY() && mousePosY <= m_tiles[i].getPosY() + 100) && 
			mouseStatus && !m_isDragging)
		{
			m_tiles[i].setSizeSmall(true);
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
		m_tiles[i].printLetter();
		j = j + 105;
	}

	//IF ARRASTRANT
	if (m_isDragging) { //s'esta arrastrant per la partida?
		m_tiles[m_tileDragging].setPos(mousePosX, mousePosY);
		if (!mouseStatus) //està arrestrant pero ha deixat anar el boto?
		{
			m_isDragging = false;
			PositionResult result;
			float cellSize = (BOARD_SIZE / BOARD_COLS_AND_ROWS);
			int col = int((mousePosX - BOARD_POS_X) / cellSize);
			int row = int((mousePosY - BOARD_POS_Y) / cellSize);
			BoardPosition boardPos(col, row);
			int colDef, rowDef;
			if (mousePosX < BOARD_POS_X || mousePosX > BOARD_POS_X + BOARD_SIZE ||
				mousePosY < BOARD_POS_Y || mousePosY > BOARD_POS_Y + BOARD_SIZE || !board.getCell(row, col).getEmpty()) 
			{ 
				//fora del taulell a les X o les Y
				result = INVALID_POSITION;
				m_tiles[m_tileDragging].setIsOnBoard(false);
			}
			else {

				if (m_tiles[m_tileDragging].getIsOnBoard()) {  //borro paraula i torno a fer tots els set tiles per a que no es dupliqui un setTile
					board.removeCurrentWord();
					for (int i = 0; i < m_vSetTiles.size(); i++) {
						if (m_vSetTiles[i].first.getLetter() == m_tiles[m_tileDragging].getTile().getLetter()) {
							result = board.setTile(m_tiles[m_tileDragging].getTile(), boardPos);

							m_tiles[m_tileDragging].setIsOnBoard(true);
							m_tiles[m_tileDragging].setSizeSmall(true);
						}
						else {
							result = board.setTile(m_vSetTiles[i].first, m_vSetTiles[i].second);

						}
					}
				}
				else {
					result = board.setTile(m_tiles[m_tileDragging].getTile(), boardPos); //comprovem si la paraula es correcte amb el setTile
					m_vSetTiles.push_back(make_pair(m_tiles[m_tileDragging].getTile(), boardPos));
					m_tiles[m_tileDragging].setIsOnBoard(true);
					m_tiles[m_tileDragging].setSizeSmall(true);
				}

				cout << "PARAULA SETTILE: " << m_tiles[m_tileDragging].getTile().getLetter() << endl;

				float posY = boardPos.getRow() * cellSize + BOARD_POS_Y;
				float posX = boardPos.getCol() * cellSize + BOARD_POS_X;
				m_tiles[m_tileDragging].setPos(posX, posY);
			}
			switch (result) {
			case INVALID_POSITION:
				m_tiles[m_tileDragging].setSizeSmall(false);
				m_tiles[m_tileDragging].setIsOnBoard(false); //isOnBoard = false --> pickupFromBoard()
				m_allCorrect = false;
				break;
			case NOT_EMPTY:
				m_tiles[m_tileDragging].setSizeSmall(false);
				break;
			case VALID_POSITION:
				m_tiles[m_tileDragging].setSizeSmall(true);
				m_tiles[m_tileDragging].setIsOnBoard(true); //isOnBoard = true --> leaveOnBoard()
				break;
			default:
				break;
			}
		}
	}
}

void Player::render(int mousePosX, int mousePosY, bool mouseStatus)
{
	/*
	int posX = 4;
	int posY = 645;
	
	for (int i = 0; i < MAX_TILES; i++)
	{
		if (m_tiles[i].getIsMoving() == false && m_tiles[i].getIsEmpty() == false && m_tiles[i].getIsOnBoard() == false)
		{
			switch (m_tiles[i].getTile().getLetter())
			{
				case 'a':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'b':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_B_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'c':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_C_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'd':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_D_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'e':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_E_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'f':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_F_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'g':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_G_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'h':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_H_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'i':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_I_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'j':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_J_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'k':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_K_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'l':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_L_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'm':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_M_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'n':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_N_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'o':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_O_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'p':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_P_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'q':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Q_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'r':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_R_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 's':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_S_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 't':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_T_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'u':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_U_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'v':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_V_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'w':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_W_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'x':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_X_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'y':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Y_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				case 'z':
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Z_BIG, posX, posY);
					m_tiles[i].setPos(posX, posY);
					break;

				default:
					break;
			}
			posX += 107;
		}

		else if (m_tiles[i].getIsMoving() == true)
		{
			switch (m_tiles[i].getTile().getLetter())
			{
			case 'a':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'b':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_B_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'c':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_C_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'd':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_D_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'e':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_E_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'f':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_F_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'g':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_G_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'h':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_H_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'i':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_I_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'j':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_J_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'k':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_K_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'l':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_L_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'm':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_M_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'n':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_N_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'o':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_O_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'p':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_P_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'q':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Q_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'r':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_R_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 's':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_S_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 't':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_T_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'u':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_U_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'v':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_V_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'w':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_W_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'x':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_X_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'y':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Y_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			case 'z':
				GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Z_SMALL, mousePosX, mousePosY);
				m_tiles[i].setPos(mousePosX, mousePosY);
				break;

			default:
				break;
		}
		}
	}
	*/
	
}

