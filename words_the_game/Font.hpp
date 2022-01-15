#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Font : public sf::Font
{
public:
	Font(std::string path);
};