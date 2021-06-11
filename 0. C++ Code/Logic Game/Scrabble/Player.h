#ifndef Player_hpp
#define Player_hpp

#include "../Scrabble_Defs.h"
#include "PlayerTile.h"
#include "Board.h"

class Player
{
public:
	// Constructors i Destructor
	Player() { m_score = 0; }
	~Player() {}

	// Getters
	int getPlayerScore() const { return m_score; }
	
	// Setters
	void setPlayerScore(const int& score) { m_score = score; }
	void setPlayerTile(Tile tile);

	// Update
	void update(int mousePosX, int mousePosY, bool mouseStatus, Board& board);

	// Render
	void render(int mousePosX, int mousePosY, bool mouseStatus);

private:
	PlayerTile m_tiles[MAX_TILES];
	int m_score;
};

#endif /* Player_hpp */
