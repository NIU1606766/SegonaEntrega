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

class ScrabbleGame
{
public:
    ScrabbleGame();
    ~ScrabbleGame();
    
    void updateAndRender    (int mousePosX, int mousePosY,bool mouseStatus);
    
    
private:
	
    Button m_send;
    bool m_buttonPressed;
    bool m_drawLetter;

};

#endif /* ScrabbleGame_hpp */
