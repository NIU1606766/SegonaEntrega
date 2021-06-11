//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include "../GraphicManager.h"
#include "../Scrabble_Defs.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string fitxerConfig = "data/Configuration/board.txt";


Board::Board()
{
	ifstream fitxer;
	fitxer.open(fitxerConfig);

	if (fitxer.is_open())
	{
		int row, col;
		string effect;
		vector<int> fila;
		vector<int> columna;
		vector<string> efecte;

		fitxer >> row >> col >> effect;

		while (!fitxer.eof())
		{
			fila.push_back(row);
			columna.push_back(col);
			efecte.push_back(effect);
			fitxer >> row >> col >> effect;
		}

		ScoreEffect s;

		for (int i = 0; i < fila.size(); i++)
		{
			if (efecte[i] == "DL")
				s = DL;
			else if (efecte[i] == "TL")
				s = TL;
			else if (efecte[i] == "DW")
				s = DW;
			else if (efecte[i] == "TW")
				s = TW;
			else
				s = NO_EFFECT;

			m_cells[fila[i]][columna[i]].setScoreEffect(s);
		}

		fitxer.close();
	}
}

PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	int row = boardPos.getRow();
	int col = boardPos.getCol();

	if (row < 0 || row >= BOARD_COLS_AND_ROWS || col < 0 || col >= BOARD_COLS_AND_ROWS)
	{
		return INVALID_POSITION; //la posició està fora del taulell
	}

	if (m_cells[row][col].getEmpty() == false)
	{
		return NOT_EMPTY; //ja hi ha una fitxa en aquesta cel·la
	}

	m_cells[row][col].setTile(tile); //posem la fitxa al taulell
	m_cells[row][col].setEmpty(false);

	m_currentWord.push_back(boardPos); //guardem la posició de la fitxa al vector "m_currentWord"

	return VALID_POSITION;
}

bool Board::aligned()
{
	m_horizontal = true;
	m_vertical = false;
	int i;
	for (i = 0; i < m_currentWord.size(); i++)
	{
		if (m_currentWord[i].getRow() != m_currentWord[0].getRow()) //comprovem que totes les cel·les estiguin a la mateixa fila
		{
			m_horizontal = false;
		}
	}
	if (m_horizontal == false)
	{
		for (i = 0; i < m_currentWord.size(); i++)
		{
			if (m_currentWord[i].getCol() != m_currentWord[1].getCol()) //comprovem que totes les cel·les estiguin a la mateixa columna
			{
				return false;
			}
		}
		m_vertical = true;
	}

	if (m_horizontal == true)
	{
		m_min = m_currentWord[0].getCol();
		m_max = m_currentWord[0].getCol();
		for (i = 0; i < m_currentWord.size(); i++)
		{
			if (m_currentWord[i].getCol() < m_min) //seleccionem la primera casella de la paraula
			{
				m_min = m_currentWord[i].getCol();
			}
			if (m_currentWord[i].getCol() > m_max) //seleccionem la última casella de la paraula
			{
				m_max = m_currentWord[i].getCol();
			}
		}
		for (i = m_min + 1; i < m_max; i++)
		{
			if (m_cells[m_currentWord[1].getRow()][i].getEmpty() == true) //comprovem que no hi hagi cap cel·la buida entre la primera i la última
			{
				return false;
			}
		}
	}
	else
	{
		m_min = m_currentWord[1].getRow();
		m_max = m_currentWord[1].getRow();
		for (i = 0; i < m_currentWord.size(); i++)
		{
			if (m_currentWord[i].getRow() < m_min) //seleccionem la primera casella de la paraula
			{
				m_min = m_currentWord[i].getRow();
			}
			if (m_currentWord[i].getRow() > m_max) //seleccionem la última casella de la paraula
			{
				m_max = m_currentWord[i].getRow();
			}
		}
		for (i = m_min + 1; i < m_max; i++)
		{
			if (m_cells[i][m_currentWord[1].getCol()].getEmpty() == true) //comprovem que no hi hagi cap cel·la buida entre la primera i la última
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::startInCenter()
{
	if (m_cells[7][7].getEmpty() == true) //comprovem que la casella central no estigui buida
	{
		return false;
	}
	return true;
}

bool Board::moreThanOneLetter()
{
	if (m_cells[7][8].getEmpty() && m_cells[7][6].getEmpty() && m_cells[8][7].getEmpty() && m_cells[6][7].getEmpty()) //Comprovem que les caselles que envolten la casella central no estiguin buides
	{
		return false;
	}
	return true;
}

bool Board::connection()
{
	int i, row, col;
	bool connection = false;
	BoardPosition pos;
	if (m_cells[7][7].getTilePlayed() == true)
	{
		for (i = 0; i < m_currentWord.size(); i++)
		{
			row = m_currentWord[i].getRow();
			col = m_currentWord[i].getCol();
			pos.setCol(col);
			pos.setRow(row);
			if (row > 0 && m_cells[row - 1][col].getTilePlayed() == true) //comprovem si la cel·la té una fitxa jugada a sobre
			{
				connection = true;
				pos.setRow(row - 1);
				m_verticalConnections.push_back(pos);
			}
			if (row < 14 && m_cells[row + 1][col].getTilePlayed() == true) //comprovem si la cel·la té una fitxa jugada a sota
			{
				connection = true;
				pos.setRow(row + 1);
				m_verticalConnections.push_back(pos);
			}
			if (col > 0 && m_cells[row][col - 1].getTilePlayed() == true) //comprovem si la cel·la té una fitxa jugada a l'esquerra
			{
				connection = true;
				pos.setCol(col - 1);
				m_horizontalConnections.push_back(pos);
			}
			if (col < 14 && m_cells[row][col + 1].getTilePlayed() == true) //comprovem si la cel·la té una fitxa jugada a la dreta
			{
				connection = true;
				pos.setCol(col + 1);
				m_horizontalConnections.push_back(pos);
			}
		}
	}
	else //si no és el primer torn no cal comprovar que les fitxes d'aquest torn estiguin connectades amb les dels anteriors
	{
		connection = true;
	}
	return connection;
}

bool Board::wordInDictionary() //aquest mètode només s'utilitza quan és el primer torn
{
	int i;
	Tile t;
	string word;
	vector<Cell> paraula;
	if (m_horizontal == true)
	{
		for (i = 0; i < m_currentWord.size(); i++)
		{
			t = m_cells[m_currentWord[0].getRow()][m_min + i].getTile();
			word += t.getLetter(); //guardem les lletres fitxa a fitxa a l'string "word"
			paraula.push_back(m_cells[m_currentWord[0].getRow()][m_min + i]); //també guardem les cel·les de la paraula al vector "paraula"
		}
	}
	else
	{
		for (i = 0; i < m_currentWord.size(); i++)
		{
			t = m_cells[m_min + i][m_currentWord[0].getCol()].getTile();
			word += t.getLetter(); //guardem les lletres fitxa a fitxa a l'string "word"
			paraula.push_back(m_cells[m_currentWord[0].getRow()][m_min + i]); //també guardem les cel·les de la paraula al vector "paraula"
		}
	}
	m_currentWords.push_back(paraula); //guardem la "paraula" a la matriu de paraules "m_currentWords"
	return m_dictionary.checkWord(word); //comprovem que la paraula estigui al diccionari
}
bool Board::wordsInDictionary()
{
	int i, row, col;
	Tile t;
	string word;
	vector<Cell> paraula;
	vector<string> CurrentWordsStrings;

	if (m_horizontal == true)
	{
		col = m_min;
		row = m_currentWord[0].getRow();
		while (col > 0 && m_cells[row][col - 1].getEmpty() == false)
		{
			col--; //anem fins la primera casella de la paraula
		}
		do
		{
			t = m_cells[row][col].getTile();
			word += t.getLetter(); //guardem les lletres fitxa a fitxa a l'string "word"
			paraula.push_back(m_cells[row][col]);  //també guardem les cel·les de la paraula al vector "paraula"
			col++;
		} while (col < BOARD_COLS_AND_ROWS && m_cells[row][col].getEmpty() == false); //anem fins la última casella de la paraula

		CurrentWordsStrings.push_back(word); //guardem la paraula al vector d'strings "CurrentWordsStrings"
		m_currentWords.push_back(paraula); //guardem la "paraula" a la matriu de paraules "m_currentWords"
		word = ""; 
		paraula.clear(); //resetegem "word" i "paraula"

		if (m_verticalConnections.empty() == false) //guardarem més paraules en cas d'haver-hi connexions vertcals
		{
			for (i = 0; i < m_verticalConnections.size(); i++)
			{
				row = m_verticalConnections[i].getRow();
				col = m_verticalConnections[i].getCol();
				while (row > 0 && m_cells[row - 1][col].getEmpty() == false)
				{
					row--; //anem fins la primera casella de la paraula
				}
				do
				{
					t = m_cells[row][col].getTile();
					word += t.getLetter(); //guardem les lletres fitxa a fitxa a l'string "word"
					paraula.push_back(m_cells[row][col]); //també guardem les cel·les de la paraula al vector "paraula"
					row++;
				} while (row < BOARD_COLS_AND_ROWS && m_cells[row][col].getEmpty() == false); //anem fins la última casella de la paraula

				CurrentWordsStrings.push_back(word); //guardem la paraula al vector d'strings "CurrentWordsStrings"
				m_currentWords.push_back(paraula); //guardem la "paraula" a la matriu de paraules "m_currentWords"
				word = "";
				paraula.clear(); //resetegem "word" i "paraula"
			}
		}
	}
	else //fem el mateix però amb la paraula en vertical
	{
		row = m_min;
		col = m_currentWord[0].getCol();
		while (row > 0 && m_cells[row - 1][col].getEmpty() == false)
		{
			row--;
		}
		do
		{
			t = m_cells[row][col].getTile();
			word += t.getLetter();
			paraula.push_back(m_cells[row][col]);
			row++;
		} while (row < BOARD_COLS_AND_ROWS && m_cells[row][col].getEmpty() == false);
		CurrentWordsStrings.push_back(word);
		m_currentWords.push_back(paraula);
		word = "";
		paraula.clear();

		if (m_horizontalConnections.empty() == false)
		{
			for (i = 0; i < m_horizontalConnections.size(); i++)
			{
				row = m_horizontalConnections[i].getRow();
				col = m_horizontalConnections[i].getCol();
				while (col > 0 && m_cells[row][col - 1].getEmpty() == false)
				{
					col--;
				}
				do
				{
					t = m_cells[row][col].getTile();
					word += t.getLetter();
					paraula.push_back(m_cells[row][col]);
					col++;
				} while (col < BOARD_COLS_AND_ROWS && m_cells[row][col].getEmpty() == false);
				CurrentWordsStrings.push_back(word);
				m_currentWords.push_back(paraula);
				word = "";
				paraula.clear();
			}
		}
	}
	for (i = 0; i < CurrentWordsStrings.size(); i++)
	{
		if (m_dictionary.checkWord(CurrentWordsStrings[i]) == false) //comprovem que totes les paraules formandes en aquest torn estiguin al diccionari
		{
			return false;
		}
	}
	return true;
}

int Board::score()
{
	int i, j, p = 0, letterScore, wordScore;
	bool dw, tw;
	for (i = 0; i < m_currentWords.size(); i++)
	{
		dw = false;
		tw = false;
		wordScore = 0; //inicialitzem la puntuació de la paraula a 0
		for (j = 0; j < m_currentWords[i].size(); j++)
		{
			letterScore = m_currentWords[i][j].getTile().getScore();
			if (m_currentWords[i][j].getTilePlayed() == false)
			{
				switch (m_currentWords[i][j].getScoreEffect())
				{
				case DL:
					letterScore *= 2; //si la casella té el bonus DL, multipliquem el valor de la lletra per 2
					break;
				case TL:
					letterScore *= 3; //si la casella té el bonus TL, multipliquem el valor de la lletra per 3
					break;
				case DW:
					dw = true;
					break;
				case TW:
					tw = true;
					break;
				case NO_EFFECT:
					break;
				}
			}
			wordScore += letterScore; //sumem la puntuació de la lletra a la paraula
		}
		if (dw == true)
		{
			wordScore *= 2; //si alguna casella té el bonus DW, multipliquem el valor de la paraula per 2
		}
		if (tw == true)
		{
			wordScore *= 3; //si alguna casella té el bonus TW, multipliquem el valor de la paraula per 3
		}
		p += wordScore; //sumem la puntuació de la paraula al total
	}
	return p;
}

CurrentWordResult Board::checkCurrentWord(int& points)
{
	if (aligned() == false)
	{
		return INVALID_NOT_ALIGNED; //no estan alineades o consecutives
	}
	if (m_cells[7][7].getTilePlayed() == false) //les següents comprovacions s'efectuen només el primer torn de la partida
	{
		if (startInCenter() == false)
		{
			return INVALID_START_NOT_IN_CENTER; //no s'ha començat al centre
		}
		if (moreThanOneLetter() == false)
		{
			return INVALID_WORD_OF_ONE_LETTER; //la paraula és d'una sola lletra
		}
		if (wordInDictionary() == false)
		{
			return INVALID_WORDS_NOT_IN_DICTIONARY; //la paraula no està al diccionari
		}
	}
	else
	{
		if (connection() == false)
		{
			return INVALID_NOT_CONNECTION; //la paraula no està connectada a cap fitxa de trons anteriors
		}
		if (wordsInDictionary() == false)
		{
			return INVALID_WORDS_NOT_IN_DICTIONARY; //hi ha paraules que no estan al diccionari
		}
	}
	points = score(); //sumem els punts d'aquest torn

	return ALL_CORRECT; //ha passat totes les comprovacions correctament
}

void Board::sendCurrentWordToBoard()
{
	int i;
	for (i = 0; i < m_currentWord.size(); i++)
	{
		m_cells[m_currentWord[i].getRow()][m_currentWord[i].getCol()].setTilePlayed(true); //marquem les caselles d'aquest torn com a vàlides
	}
	m_currentWord.clear(); //resetegem tots els paràmetres d'aquest torn
	m_currentWords.clear();
	m_horizontalConnections.clear();
	m_verticalConnections.clear();
}

void Board::removeCurrentWord()
{
	int i;
	Tile nullTile;
	for (i = 0; i < m_currentWord.size(); i++)
	{
		m_cells[m_currentWord[i].getRow()][m_currentWord[i].getCol()].setEmpty(true); //marquem les caselles d'aquest torn com a buides
		m_cells[m_currentWord[i].getRow()][m_currentWord[i].getCol()].setTile(nullTile); //posem una fitxa nul·la a la casella
	}
	m_currentWord.clear(); //resetegem tots els paràmetres d'aquest torn
	m_currentWords.clear();
	m_horizontalConnections.clear();
	m_verticalConnections.clear();
}

void Board::render()
{
	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, BOARD_POS_X, BOARD_POS_Y);
	int posX = BOARD_POS_X;
	int posY = BOARD_POS_Y;

	for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
		{
			m_cells[i][j].render(posX, posY);
			posX += BOARD_TILE_SIZE;
		}
		posY += BOARD_TILE_SIZE;
		posX = BOARD_POS_X;
	}
}