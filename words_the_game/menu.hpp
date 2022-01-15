#pragma once
#include <vector>
#include "Elements.hpp"
#include <utility>

struct Menu
{
	Menu(){}
	Menu(std::vector <Element*> UIList) : UIList(std::move(UIList)) {}
	std::vector <Element*> UIList;
};