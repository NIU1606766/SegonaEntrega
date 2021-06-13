//
//  ScrabbleGame.hpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef ScrabbleGame_hpp
#define ScrabbleGame_hpp

#include <stdio.h>
#include "Button.h"
#include "Board.h"
#include "LettersBag.h"
#include "Player.h"
#include "../Scrabble_Defs.h"
#include "../GraphicManager.h"


class ScrabbleGame
{
public:
    ScrabbleGame();
    
    void updateAndRender    (int mousePosX, int mousePosY,bool mouseStatus);
    
    
private:
    Board m_board;
    Player m_players[NUM_PLAYERS];
    LettersBag m_lettersBag;
    int m_currentPlayer;
    Button m_buttonRecall;
    Button m_buttonShuffle;
    Button m_buttonSend;
    Button m_buttonPass;
    int m_nPasses;
    bool m_gameOver;
};

#endif /* ScrabbleGame_hpp */
