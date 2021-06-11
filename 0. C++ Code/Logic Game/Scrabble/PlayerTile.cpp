#include "PlayerTile.h"
#include "../GraphicManager.h"

PlayerTile::PlayerTile()
{
	Tile tile;

	m_tile = tile;
	m_isEmpty = true;
	m_isOnBoard = false;
	m_isMoving = false;
}
