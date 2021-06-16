#include "PlayerTile.h"


PlayerTile::PlayerTile()
{
	// Assigna els atributs als valors per defecte que toquen.
	Tile tile;

	m_tile = tile;
	m_isEmpty = true;
	m_isOnBoard = false;
	m_sizeSmall = false;
}

void PlayerTile::printLetter()
{
	// Si la lletra no està al board i no està en petita:
	if (!m_isOnBoard && !m_sizeSmall)
	{
		// Creem un imagename amb el imagename de la lletra en big i després la renderitzem on toqui.
		IMAGE_NAME i = imageBig(m_tile.getLetter());
		GraphicManager::getInstance()->drawSprite(i, m_posX, m_posY);
	}
	// En canvi, si està al tauler o ja estava petita, la hem de dibuixar en petit.
	else if (m_isOnBoard || m_sizeSmall)
	{
		IMAGE_NAME i = imageSmall(m_tile.getLetter());
		GraphicManager::getInstance()->drawSprite(i, m_posX, m_posY);
	}
}

IMAGE_NAME PlayerTile::imageBig(char letter)
{
	// Retornem un IMAGE_LETTER_BIG de la letter que ens passen per paràmetre.
	switch (letter)
	{
	case 'a':
		return IMAGE_LETTER_A_BIG;
		break;

	case 'b':
		return IMAGE_LETTER_B_BIG;
		break;

	case 'c':
		return IMAGE_LETTER_C_BIG;
		break;

	case 'd':
		return IMAGE_LETTER_D_BIG;
		break;

	case 'e':
		return IMAGE_LETTER_E_BIG;
		break;

	case 'f':
		return IMAGE_LETTER_F_BIG;
		break;

	case 'g':
		return IMAGE_LETTER_G_BIG;
		break;

	case 'h':
		return IMAGE_LETTER_H_BIG;
		break;

	case 'i':
		return IMAGE_LETTER_I_BIG;
		break;

	case 'j':
		return IMAGE_LETTER_J_BIG;
		break;

	case 'k':
		return IMAGE_LETTER_K_BIG;
		break;

	case 'l':
		return IMAGE_LETTER_L_BIG;
		break;

	case 'm':
		return IMAGE_LETTER_M_BIG;
		break;

	case 'n':
		return IMAGE_LETTER_N_BIG;
		break;

	case 'o':
		return IMAGE_LETTER_O_BIG;
		break;

	case 'p':
		return IMAGE_LETTER_P_BIG;
		break;

	case 'q':
		return IMAGE_LETTER_Q_BIG;
		break;

	case 'r':
		return IMAGE_LETTER_R_BIG;
		break;

	case 's':
		return IMAGE_LETTER_S_BIG;
		break;

	case 't':
		return IMAGE_LETTER_T_BIG;
		break;

	case 'u':
		return IMAGE_LETTER_U_BIG;
		break;

	case 'v':
		return IMAGE_LETTER_V_BIG;
		break;

	case 'w':
		return IMAGE_LETTER_W_BIG;
		break;

	case 'x':
		return IMAGE_LETTER_X_BIG;
		break;

	case 'y':
		return IMAGE_LETTER_Y_BIG;
		break;

	case 'z':
		return IMAGE_LETTER_Z_BIG;
		break;

	default:
		break;
	}
}

IMAGE_NAME PlayerTile::imageSmall(char letter)
{
	// Retornem un IMAGE_LETTER_SMALL de la letter que ens passin per paràmetre.
	switch (letter)
	{
	case 'a':
		return IMAGE_LETTER_A_SMALL;
		break;

	case 'b':
		return IMAGE_LETTER_B_SMALL;
		break;

	case 'c':
		return IMAGE_LETTER_C_SMALL;
		break;

	case 'd':
		return IMAGE_LETTER_D_SMALL;
		break;

	case 'e':
		return IMAGE_LETTER_E_SMALL;
		break;

	case 'f':
		return IMAGE_LETTER_F_SMALL;
		break;

	case 'g':
		return IMAGE_LETTER_G_SMALL;
		break;

	case 'h':
		return IMAGE_LETTER_H_SMALL;
		break;

	case 'i':
		return IMAGE_LETTER_I_SMALL;
		break;

	case 'j':
		return IMAGE_LETTER_J_SMALL;
		break;

	case 'k':
		return IMAGE_LETTER_K_SMALL;
		break;

	case 'l':
		return IMAGE_LETTER_L_SMALL;
		break;

	case 'm':
		return IMAGE_LETTER_M_SMALL;
		break;

	case 'n':
		return IMAGE_LETTER_N_SMALL;
		break;

	case 'o':
		return IMAGE_LETTER_O_SMALL;
		break;

	case 'p':
		return IMAGE_LETTER_P_SMALL;
		break;

	case 'q':
		return IMAGE_LETTER_Q_SMALL;
		break;

	case 'r':
		return IMAGE_LETTER_R_SMALL;
		break;

	case 's':
		return IMAGE_LETTER_S_SMALL;
		break;

	case 't':
		return IMAGE_LETTER_T_SMALL;
		break;

	case 'u':
		return IMAGE_LETTER_U_SMALL;
		break;

	case 'v':
		return IMAGE_LETTER_V_SMALL;
		break;

	case 'w':
		return IMAGE_LETTER_W_SMALL;
		break;

	case 'x':
		return IMAGE_LETTER_X_SMALL;
		break;

	case 'y':
		return IMAGE_LETTER_Y_SMALL;
		break;

	case 'z':
		return IMAGE_LETTER_Z_SMALL;
		break;

	default:
		break;
	}
}
