#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "LettersBag.h"

LettersBag::LettersBag()
{
	const char* nomFitxer = "data/Configuration/lettersBag.txt";

	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		char lletra;
		int score, n_Repeticions;

		fitxer >> lletra >> score >> n_Repeticions;

		while (!fitxer.eof())
		{
			Tile tile;
			tile.setLetter(lletra);
			tile.setScore(score);
			for (int i = 1; i < n_Repeticions; i++)
			{
				m_letters.push_back(tile);
			}

			fitxer >> lletra >> score >> n_Repeticions;
		}

	}
}

Tile LettersBag::getLetter() const
{
	srand(time(0));
	int rnd = (rand() % m_letters.size()) + 1;
	Tile tile = m_letters[rnd];
	delete &m_letters[rnd];
	return tile;
}