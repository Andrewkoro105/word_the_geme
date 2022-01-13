#pragma once
#include <map>
#include "Player.hpp"
#include "Word.hpp"
#include "menu.hpp"
#include "Elements.hpp"

namespace varibles
{
	extern Menu localGame, startBot, startLocal, startOnlineá, end, mainMenu, * nowElements;

	extern std::vector<Player> names;

	extern std::map <char, std::vector<std::string>> words;

	extern std::map <wchar_t, std::vector<word>> grWords;
}