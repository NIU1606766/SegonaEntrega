#ifndef Player_hpp
#define Player_hpp

#include "../Scrabble_Defs.h"
#include "PlayerTile.h"
#include "LettersBag.h"
#include "Board.h"

class Player
{
public:
	// Constructors i Destructor
	Player() { m_score = 0; m_isDragging = false; }
	~Player() {}

	// Getters
	int getPlayerScore() const { return m_score; }
	
	// Setters
	void setPlayerScore(const int& score) { m_score = score; }

	// Update
	void update(int mousePosX, int mousePosY, bool mouseStatus, Board& board);

	// Render
	void render(int mousePosX, int mousePosY, bool mouseStatus);

	
	void addTiles(LettersBag& lb);
	bool sendCurrentWordToBoard(Board& board);
	bool anyTileOnTheBoard();
	bool allTilesPlayed();
	IMAGE_NAME imageSmall2(char letter);
	void checkBoard(Board& board);
	void recall();
	void shuffle();
	bool noTiles();


private:
	PlayerTile m_tiles[MAX_TILES];
	int m_score;
	int m_tileDragging;
	bool m_isDragging;
	bool m_allCorrect;

	vector <pair<float, float>> m_boardTilesPosition;
	vector <Tile> m_boardTiles;
	vector <pair<Tile, BoardPosition>> m_setTiles;
};

#endif /* Player_hpp */
