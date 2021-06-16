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
	if (mousePosX >= m_iPosX && mousePosY >= m_iPosY && mousePosX <= m_iPosX + m_iWidth && mousePosY <= m_iPosY + m_iHeight) // Comprovem que el mouse està dins el botó
    {
        if (mouseIsPressed && m_eCurrentState == NORMAL) // Hem apretat el botó
        {
            m_eCurrentState = PRESSED; // Quan apretem el botó encara no activem l'acció
        }
        else if (!mouseIsPressed && m_eCurrentState == PRESSED) // Hem deixat d'apretar
        {
            doAction = true; // Quan el deixem anar sí que l'activem
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
        GraphicManager::getInstance()->drawSprite(m_eStatePressed, m_iPosX, m_iPosY); // Si està apretat el dibuixem apretat
    }
    else
    {
        GraphicManager::getInstance()->drawSprite(m_eStateNormal, m_iPosX, m_iPosY); // Si no ho està el dibuixem normal
    }
}

