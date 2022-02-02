#include "Localization.h"
#include <iostream>

Localization localization;

Localization::Localization(std::string startLanguage) : nowLanguage(startLanguage){}

void Localization::changeWords(std::string nowLanguage)
{
	this->nowLanguage = nowLanguage;
}

std::wstring Localization::getPhrase(std::string phrase)
{
	return words[phrase][nowLanguage] ;
}

std::vector <std::string> Localization::listLanguage()
{
	std::vector <std::string> listLang;
	for (auto& item : words["language"])
		listLang.push_back(item.first);

	return listLang;
}

const std::string Localization::getNowLenduage()
{
	return nowLanguage;
}