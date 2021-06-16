#ifndef PlayerTile_hpp
#define PlayerTile_hpp

#include "Tile.h"
#include "BoardPosition.h"
#include "../GraphicManager.h"

class PlayerTile
{
public:

	// Constructor i Deconstructor
	PlayerTile();
	PlayerTile(Tile& tile) { m_tile = tile; m_isEmpty = true; m_isOnBoard = false; }

	// Setters
	void setTile(const Tile& tile) { m_tile = tile; }
	void setIsEmpty(const bool& isEmpty) { m_isEmpty = isEmpty; }
	void setPos(float posX, float posY) { m_posX = posX; m_posY = posY; }
	void setIsOnBoard(const bool& isOnBoard) { m_isOnBoard = isOnBoard; }
	void setBoardPosition(BoardPosition& bp) { m_boardPosition = bp; }
	void setSizeSmall(const bool& isSmall) { m_sizeSmall = isSmall; }


	// Getters
	Tile getTile() { return m_tile; }
	bool getIsEmpty() const { return m_isEmpty; }
	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }
	bool getIsOnBoard() const { return m_isOnBoard; }
	BoardPosition getBoardPosition() const { return m_boardPosition; }
	bool getSizeSmall() const { return m_sizeSmall; }
	

	//Mètodes de la part gràfica
	void printLetter();
	
	IMAGE_NAME imageBig(char letter);
	IMAGE_NAME imageSmall(char letter);

	static const int bigTileSize = 100;
	static const int smallTileSize = 40;

private:
	Tile m_tile;
	bool m_isEmpty;
	float m_posX;
	float m_posY;
	bool m_isOnBoard;
	BoardPosition m_boardPosition;
	bool m_sizeSmall;
};

#endif /* PlayerTile_hpp */