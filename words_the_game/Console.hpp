#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include "Variable.hpp"



namespace console
{
	void dictionary();
	bool existence—heck(std::string wordIn);
	void eliminator(std::string& word);
	void bot();
	void defolt(std::string wordIn, std::vector<std::string> name);
	void consolStart();

	extern int chat;
	extern char exceptionLitter[];
}