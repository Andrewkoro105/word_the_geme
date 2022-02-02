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
		extern bool clic;
		extern wchar_t inputChar;
	}
	namespace menu
	{
		extern Menu BotGame, localGame, startLocal, mainMenu, * nowElements;
	}

	extern std::vector<Player> names;

	extern std::map <char, std::vector<std::string>> words;

	extern std::map <wchar_t, std::vector<word>> grWords;
}