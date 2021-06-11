#ifndef Player_hpp
#define Player_hpp

#include "../Scrabble_Defs.h"
#include "PlayerTile.h"

class Player
{
public:
	// Constructors i Destructor
	Player() { m_score = 0; }
	Player(PlayerTile playerTiles[]);
	~Player() {}

	// Getters
	int getPlayerScore() const { return m_score; }
	
	// Setters
	void setPlayerScore(const int& score) { m_score = score; }
	void setPlayerTile(Tile tile);

private:
	int m_score;
	PlayerTile m_tiles[MAX_TILES];
};

#endif /* Player_hpp */
