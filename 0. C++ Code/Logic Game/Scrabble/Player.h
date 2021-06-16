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

	
	// Altres funcions necessàries per la funció Update del Player.
	void shuffle();
	void recall();
	void addTiles(LettersBag& lb);
	bool sendCurrentWordToBoard(Board& board);
	void checkBoard(Board& board);
	IMAGE_NAME imageSmall(char letter);
	bool everyTilePlayed();
	bool noTiles();
	bool tilesOnBoard();


private:
	PlayerTile m_tiles[MAX_TILES];
	int m_score;
	int m_tileDragging;
	bool m_isDragging;
	bool m_allCorrect;

	vector <pair<Tile, BoardPosition>> m_setTiles; // --> vector de pair, que serveix per guardar quines tiles s'han jugat en el torn i la seva posició al tauler.
	vector <pair<float, float>> m_boardTilesPosition; // --> vector de pair, que guarda la posició de les tiles que estan al board.
	vector <Tile> m_boardTiles; // --> vector de tiles que guarda quines tiles queden al board.
};

#endif /* Player_hpp */
