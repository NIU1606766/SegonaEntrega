#ifndef PlayerTile_hpp
#define PlayerTile_hpp

#include "Tile.h"
#include "BoardPosition.h"

class PlayerTile
{
public:
	// Constructor i Deconstructor
	PlayerTile();
	PlayerTile(Tile& tile) { m_tile = tile; m_isEmpty = true; m_isOnBoard = false; }
	~PlayerTile() {}

	// Setters
	void setTile(const Tile& tile) { m_tile = tile; }
	void setIsEmpty(const bool& isEmpty) { m_isEmpty = isEmpty; }
	void setPos(float posX, float posY) { m_posX = posX; m_posY = posY; }
	void setIsOnBoard(const bool& isOnBoard) { m_isOnBoard = isOnBoard; }
	void setBoardPosition(BoardPosition& bp) { m_boardPosition = bp; }

	// Getters
	Tile getTile() const { return m_tile; }
	bool getIsEmpty() const { return m_isEmpty; }
	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
	bool getIsOnBoard() const { return m_isOnBoard; }
	BoardPosition getBoardPosition() const { return m_boardPosition; }

private:
	Tile m_tile;
	bool m_isEmpty;
	float m_posX;
	float m_posY;
	bool m_isOnBoard;
	BoardPosition m_boardPosition;
};

#endif /* PlayerTile_hpp */