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
	Tile getLetter() const;
	bool getEmpty() const {}
private:
	vector<Tile> m_letters;
};


#endif /* LettersBag_hpp */
