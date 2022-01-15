#include "Font.hpp"

Font::Font(std::string path)
{
	loadFromFile(path);
}