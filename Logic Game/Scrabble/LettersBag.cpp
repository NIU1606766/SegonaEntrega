#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "LettersBag.h"


LettersBag::LettersBag()
{
	m_empty = false;
	const char* nomFitxer = "data/Configuration/lettersBag.txt";

	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		char lletra;
		int score, n_Repeticions;
		Tile tile;

		fitxer >> lletra >> score >> n_Repeticions;

		while (!fitxer.eof())
		{
			tile.setLetter(lletra);
			tile.setScore(score);
			for (int i = 0; i < n_Repeticions; i++)
			{
				m_letters.push_back(tile);
			}

			fitxer >> lletra >> score >> n_Repeticions;
		}

	}
}


Tile LettersBag::getLetter()
{
	srand(time(NULL));
	int rnd = (rand() % m_letters.size());
	Tile tile = m_letters[rnd];
	m_letters.erase(m_letters.begin() + rnd);
	return tile;
}
