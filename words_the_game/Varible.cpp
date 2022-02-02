#pragma once
#include <map>
#include "Player.hpp"
#include "Word.hpp"
#include "menu.hpp"
#include "Elements.hpp"

namespace varibles
{
	namespace Input
	{
		bool clic = 0;
		wchar_t inputChar = '\0';
	}
	namespace menu
	{
		Menu* nowElements;
	}
	
	std::vector<Player> names{ {L""},  {L""}, {L""}, {L""}, {L""}, {L""} };

	std::map <char, std::vector<std::string>> words;

	std::map <wchar_t, std::vector<word>> grWords;
}