#include "Player.h"

Player::Player(PlayerTile playerTiles[])
{
	for (int i = 0; i < MAX_TILES; i++)
	{
		m_tiles[i] = playerTiles[i];
	}

	m_score = 0;
}

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
			trobat = true;
		}
	}
}