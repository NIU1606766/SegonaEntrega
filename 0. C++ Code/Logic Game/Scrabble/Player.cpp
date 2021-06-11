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
			m_tiles[i].setIsMoving(false);
			trobat = true;
		}
	}
}
void Player::update(int mousePosX, int mousePosY, bool mouseStatus, Board& board)
{
	int i = 0;
	int index;
	bool fitxaEnMoviment = false;

	while (i < MAX_TILES && !fitxaEnMoviment)
	{
		if (m_tiles[i].getIsMoving() == true)
		{
			index = i;
			fitxaEnMoviment = true;
		}

		else
			i++;
	}

	if (fitxaEnMoviment)
	{
		m_tiles[index].setPos(mousePosX, mousePosY);

		if (!mouseStatus)
		{
			int posX = BOARD_POS_X;
			int posY = BOARD_POS_Y;
			bool mouseInCell = false;
			BoardPosition bp;
			PositionResult result;
			for(int j = 0; j<BOARD_COLS_AND_ROWS; j++)
			{
				for(int i = 0; i<BOARD_COLS_AND_ROWS;i++)
				{
					if (mousePosX > posX && mousePosY > posY && mousePosX < posX + BOARD_TILE_SIZE && mousePosY < posY + BOARD_TILE_SIZE)
					{
						mouseInCell = true;
						bp.setCol(i);
						bp.setRow(j);
						m_tiles[index].setBoardPosition(bp);
						result = board.setTile(m_tiles[index].getTile(), bp);
					}
					posX += BOARD_TILE_SIZE;
				}
				posY += BOARD_TILE_SIZE;
			}

			switch (result)
			{
				case INVALID_POSITION:
					break;

				case NOT_EMPTY:
					break;

				case VALID_POSITION:

					break;
			}
		}
	}

	else
	{
		if (mouseStatus)
		{
			for (int i = 0; i < MAX_TILES; i++)
			{
				if (mousePosX >= m_tiles[i].getPosX() && mousePosY >= m_tiles[i].getPosY() && mousePosX <= m_tiles[i].getPosX() + m_tiles[i].getSize() && mousePosY <= m_tiles[i].getPosY() + m_tiles[i].getSize())
				{
					m_tiles[i].setIsMoving(true);
					m_tiles[i].setIsEmpty(true);
					m_tiles[i].setSize(m_tiles[i].smallTileSize);
					if (m_tiles[i].getIsOnBoard() == true)
					{
						m_tiles[i].setIsOnBoard(false);
						m_tiles[i].setIsEmpty(false);
						m_tiles[i].setSize(m_tiles[i].bigTileSize);
					}
				}
			}
		}
	}
}
void Player::render(int mousePosX, int mousePosY, bool mouseStatus)
{
	// Dibuixa les fitxes que té el jugador a la mà. (Si no s'estàn movent o no estan buides, es renderitzen)
	int posX = 4;
	int posY = 645;
	for (int i = 0; i < MAX_TILES; i++)
	{

		if (m_tiles[i].getIsEmpty() == false && m_tiles[i].getIsMoving() == false)
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

	}

	for (int i = 0; i < MAX_TILES; i++)
	{
		if (mouseStatus && mousePosX >= m_tiles[i].getPosX() && mousePosY >= m_tiles[i].getPosY() && mousePosX <= m_tiles[i].getPosX() + 100 && mousePosY <= m_tiles[i].getPosY() + 100 && m_tiles[i].getIsEmpty() == false)
		{
			m_tiles[i].setIsMoving(true);
			m_tiles[i].setIsEmpty(true);
			std::cout << "Tile " << i << " Moving: " << m_tiles[i].getIsMoving() << " Empty: " << m_tiles[i].getIsEmpty() << std::endl;
		}
	}


	// Trobem quina tile s'està movent
	int i = 0;
	int index;
	bool trobat = false;

	while (mouseStatus && i < MAX_TILES && !trobat)
	{
		if (m_tiles[i].getIsMoving() == true)
		{
			index = i;
			trobat = true;
		}

		else
			i++;
	}

	if (trobat)
	{
		switch (m_tiles[index].getTile().getLetter())
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

	if (!mouseStatus)
	{

		for (int i = 0; i < MAX_TILES; i++)
		{
			m_tiles[i].setIsMoving(false);
			m_tiles[i].setIsEmpty(false);
			std::cout << "Tile " << i << " Moving: " << m_tiles[i].getIsMoving() << " Empty: " << m_tiles[i].getIsEmpty() << std::endl;
		}
	}
}