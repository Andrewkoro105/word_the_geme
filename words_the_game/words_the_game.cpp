#define NOMINMAX
#include <string>
#include <vector>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Variable.hpp"
#include "Console.hpp"
#include "FunctionForElement.hpp"
#include "Font.hpp"


bool Utf8ToUtf16(std::string const& src, std::wstring& dst)
{
    if (src.empty()) {
        dst.clear();
        return true;
    }
    if (src.size() >= static_cast<size_t>(2147483647)) {
        return false;
    }
    int srcLength = static_cast<int>(src.size());
    const int utf16Length = ::MultiByteToWideChar(
        CP_UTF8, MB_ERR_INVALID_CHARS,
        src.data(), srcLength,
        nullptr, 0
    );
    if (utf16Length == 0) {
        dst.clear();
        return false;
    }
    dst.resize(utf16Length);
    const int result = ::MultiByteToWideChar(
        CP_UTF8, MB_ERR_INVALID_CHARS,
        src.data(), srcLength,
        &(dst[0]), utf16Length //если компилятор ругается на dst.data(), то &(dst[0])
    );
    if (result == 0) {
        dst.clear();
        return false;
    }
    return true;
}

void dictionary()
{
    std::stringstream ss;
    ss << std::ifstream("russian_nouns8.txt").rdbuf();
    std::wstring dictionary;
    Utf8ToUtf16(ss.str(), dictionary);

    std::wstring line = L"";

    for (int i = 0; i < dictionary.size(); i++)
    {
        if (dictionary[i] != L'\n')
            line += dictionary[i];
        else
        {
            auto it = varibles::grWords.find(line[0]);

            if (it == varibles::grWords.end())
            {
                std::vector<word> a = { word(line) };
                varibles::grWords.emplace(line[0], a);
            }
            else
                it->second.push_back(word(line));
            line = L"";
        }

    }
}

void grafic()
{
    setlocale(LC_ALL, "");

    dictionary();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Word the game");

    varibles::nowElements = &varibles::mainMenu;

    while (window.isOpen())
    {
        varibles::Input::clic = 0;

        sf::Event event;
        while (window.pollEvent(event))
        {
            std::string str;

            if (event.type == sf::Event::TextEntered)
                varibles::Input::inputChar = (wchar_t)(event.key.code);
                
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                varibles::Input::clic = 1;
        }

        window.clear(sf::Color(5, 25, 35));


        for (int i = 0; i < (*varibles::nowElements).UIList.size(); i++)
            (*varibles::nowElements).UIList[i]->handle(window);

        window.display();
    }
}

int main()
{
    srand(clock() * sf::Mouse::getPosition().x * sf::Mouse::getPosition().y);

    setlocale(LC_ALL, "");

    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    grafic();

    console::consolStart();
}