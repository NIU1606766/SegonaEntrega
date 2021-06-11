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
	void setIsMoving(const bool& isMoving) { m_isMoving = isMoving; }
	void setSize(int size) { m_size = size; }

	// Getters
	Tile getTile() { return m_tile; }
	bool getIsEmpty() const { return m_isEmpty; }
	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
	bool getIsOnBoard() const { return m_isOnBoard; }
	BoardPosition getBoardPosition() const { return m_boardPosition; }
	bool getIsMoving() const { return m_isMoving; }
	int getSize() const { return m_size; }

	
	const int bigTileSize = 100;
	const int smallTileSize = 40;

private:
	int m_size;
	Tile m_tile;
	bool m_isEmpty;
	float m_posX;
	float m_posY;
	bool m_isOnBoard;
	bool m_isMoving;
	BoardPosition m_boardPosition;
};

#endif /* PlayerTile_hpp */