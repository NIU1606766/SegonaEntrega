//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;

Dictionary::Dictionary()
{
	setLanguagesPath();
	m_currentLanguage = ENGLISH;
	string nomFitxer = m_languagePath[ENGLISH]; //COMENCEM X DEFECTE EN ANGL?S
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		string word;
		fitxer >> word;
		while (!fitxer.eof())
		{
			m_words.push_back(word);
			fitxer >> word;
		}

		fitxer.close();
	}
}

bool Dictionary::checkWord(const string& word)
{
	int i = 0;
	bool trobat = false;
	while(i < m_words.size() && !trobat)
	{
		if (m_words[i] == word)
			trobat = true;

		else
			i++;
	}

	if (trobat)
		return true;
	else
		return false;
}
