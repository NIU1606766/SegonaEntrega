//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp


class Tile
{
public:
    Tile() : m_letter('?'), m_score(-1) {}
    Tile(char letter, int score): m_letter(letter), m_score(score) {}
    char getLetter() const { return m_letter; }
    unsigned int getScore() const { return m_score; }
    void setLetter(char letter) { m_letter = letter; }
    void setScore(unsigned int score) { m_score = score; }
    
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
