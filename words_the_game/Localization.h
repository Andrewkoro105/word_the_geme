#pragma once
#include <map>
#include <vector>
#include <string>

extern class Localization
{
public:
	Localization(std::string startLanguage = "ru");
	void changeWords(std::string nowLanguage);
	std::vector <std::string> listLanguage();
	const std::string getNowLenduage();
	std::wstring getPhrase(std::string Phrase);
private:
	std::string nowLanguage;
	std::map <std::string, std::map <std::string, std::wstring>> words =
	{
		{
			"language",
			{
				{"en", L"EN"},
				{"ru", L"RU"}
			}
		},
		{
			"gameName",
			{
				{"en", L"Word the game"},
				{"ru", L"���� � �����"}
			}
		},
		{
			"gameName:local",
			{
				{"en", L"Word the game : Local"},
				{"ru", L"���� � ����� : �� 1 ��"}
			}
		},
		{
			"gameName:bot",
			{
				{"en", L"Word the game:Bot"},
				{"ru", L"���� � ����� : � �����"}
			}
		},
		{
			"local",
			{
				{"en", L"local"},
				{"ru", L"�� 1 ��"}
			}
		},
		{
			"bot",
			{
				{"en", L"bot"},
				{"ru", L"���"}
			}
		},
		{
			"online",
			{
				{"en", L"online"},
				{"ru", L"������"}
			}
		},
		{
			"start",
			{
				{"en", L"srart"},
				{"ru", L"�����"}
			}
		},
		{
			"hit",
			{
				{"en", L"hit"},
				{"ru", L"���������"}
			}
		},
		{
			"suggestions for entering a name : 1",
			{
				{"en", L"select the names of the players"},
				{"ru", L"�������� ����� �������"}
			}
		},
		{
			"suggestions for entering a name : 2",
			{
				{"en", L"in the game"},
				{"ru", L"� ����"}
			}
		}
	};
}localization;

