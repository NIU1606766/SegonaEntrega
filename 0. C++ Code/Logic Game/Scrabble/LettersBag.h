//
// LettersBag.hpp
// Scrabble
//

#ifndef LettersBag_hpp
#define LettersBag_hpp

#include <vector>
#include "Tile.h"

using namespace std;

class LettersBag
{
public:
	// Constructor i Destructor
	LettersBag();
	~LettersBag() {}

	// Getters and setters
	int getLettersBagSize() { return m_letters.size(); }
	Tile getLetter();
	bool getEmpty() const { return m_empty; }
	void setEmpty(const bool& isEmpty) { m_empty = isEmpty; }

private:
	vector<Tile> m_letters;
	bool m_empty;
};


#endif /* LettersBag_hpp */
