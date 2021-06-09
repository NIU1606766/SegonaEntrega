//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "Tile.h"

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
    Cell() { m_empty = true; m_tilePlayed = false; m_scoreEffect = NO_EFFECT; m_tile.setLetter('?'); m_tile.setScore(-1); }
    ScoreEffect getScoreEffect() { return m_scoreEffect; }
    Tile getTile() { return m_tile; }
    bool getEmpty() { return m_empty; }
    bool getTilePlayed() { return m_tilePlayed; }
    void setScoreEffect(ScoreEffect scoreEffect) { m_scoreEffect = scoreEffect; }
    void setTile(Tile tile) { m_tile = tile; }
    void setEmpty(bool empty) { m_empty = empty; }
    void setTilePlayed(bool tilePlayed) { m_tilePlayed = tilePlayed; }

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
