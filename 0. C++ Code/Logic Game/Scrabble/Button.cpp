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
	if (mouseIsPressed && mousePosX >= m_iPosX && mousePosY >= m_iPosY && mousePosX <= m_iPosX + m_iWidth && mousePosY <= m_iPosY + m_iHeight)
    {
        m_eCurrentState = PRESSED;
        return true;
    }
    else
    {
        m_eCurrentState = NORMAL;
        return false;
    }
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

