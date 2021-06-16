#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "LettersBag.h"


LettersBag::LettersBag()
{
	// Declarem que la LettersBag no està buida i guardem el nom del fitxer del que hem de llegir.
	m_empty = false;
	const char* nomFitxer = "data/Configuration/lettersBag.txt";

	ifstream fitxer;
	fitxer.open(nomFitxer);

	// Llegim del fitxer totes les lletres que hi han, la score que tenen i ho guardem en un vector de Tile anomenat m_letters.
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
	// Generem un nombre aleatori entre zero i m_letters.size()
	srand(time(NULL));
	int rnd = (rand() % m_letters.size());

	// Creem una Tile auxiliar que sigui la m_letters[rnd]
	Tile tile = m_letters[rnd];

	// Borrem del vector de Tiles la que hem fet servir per copiar a l'auxiliar.
	m_letters.erase(m_letters.begin() + rnd);

	// Retornem la tile auxiliar.
	return tile;
}
