//
//  Dictionary.hpp
#pragma once

#include "Scrabble.h"
#include <stdio.h>
#include <iostream>

const string englishDic = "data/Dictionaries/English.dic";
const string catalanDic = "data/Dictionaries/Catalan.dic";
const string spanishDic = "data/Dictionaries/Spanish.dic";

typedef enum {
    CATALAN = 0,
    SPANISH,
    ENGLISH,
    NO_LANGUAGE
} Language;

class Dictionary
{
public:
    Dictionary();
    //~Dictionary();

    void setLanguage(Language language) { m_currentLanguage = language; }
    Language getCurrentLanguage() { return m_currentLanguage; }
    void setLanguagesPath() {
        m_languagePath[CATALAN] = catalanDic;
        m_languagePath[SPANISH] = spanishDic;
        m_languagePath[ENGLISH] = englishDic;
    }
    bool checkWord(const string& word);

private:
	vector<string> m_words;
    string m_languagePath[NO_LANGUAGE];
    Language m_currentLanguage;
    
};
