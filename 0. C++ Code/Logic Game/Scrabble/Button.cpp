//
//  Button.cpp

#include "Button.h"

Button::Button(IMAGE_NAME state_normal,
               IMAGE_NAME state_pressed,
               int posX, int posY,
               int width, int height)
{
    m_eCurrentState = NORMAL;
    m_iPosX = posX;
    m_iPosY = posY;
    m_iWidth = width;
    m_iHeight = height;
    m_eStateNormal = state_normal;
    m_eStatePressed = state_pressed;
}

Button::~Button()
{

}


bool Button::update (int mousePosX, int mousePosY, bool mouseIsPressed) 
{
    bool doAction = false;
	if (mouseIsPressed && mousePosX >= m_iPosX && mousePosY >= m_iPosY && mousePosX <= m_iPosX + m_iWidth && mousePosY <= m_iPosY + m_iHeight)
    {
        if (mouseIsPressed && m_eCurrentState == NORMAL)
        {
            m_eCurrentState = PRESSED; // Hem entrat amb el mouse apretant i per tant no cal fer res.
        }
        else if (!mouseIsPressed && m_eCurrentState == PRESSED)
        {
            doAction = true;
            m_eCurrentState = NORMAL;
        }
    }
    else
    {
        m_eCurrentState = NORMAL;
    }

    return doAction;
}

void Button::render ()
{
    if (m_eCurrentState == PRESSED)
    {
        GraphicManager::getInstance()->drawSprite(m_eStatePressed, m_iPosX, m_iPosY);
    }
    else
    {
        GraphicManager::getInstance()->drawSprite(m_eStateNormal, m_iPosX, m_iPosY);
    }
}

