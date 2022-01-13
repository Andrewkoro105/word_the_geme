#define NOMINMAX
#include <string>
#include <vector>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Variable.hpp"
#include "Console.hpp"
#include "FunctionForElement.hpp"


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

    bool clic = 0;
    wchar_t inputChar = '\0';

    sf::RenderWindow window(sf::VideoMode(800, 600), "Word the game");

    //create font
    sf::Font font;
    font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");

    //-------[mainMenu]
    
    //create the button sprite
    SprElement sprBut("image/main/but.png");
    sf::Sprite spriteBut = sprBut.sprite;

    SprElement maimBacking("image/mainMenu/backing.png", sf::Vector2f(400, 300), &varibles::mainMenu.UIList);

    TextElem NameGame(L"Word the game", sf::Vector2f(400, 150), font, &varibles::mainMenu.UIList, sf::Color(0, 166, 251), 35);

    Button butOnline(&clic, But::MainB::online, sf::IntRect(27, 300, 230, 90),spriteBut, TextElem(L"online", sf::Vector2f(), font, 0, sf::Color(255, 25, 35), 25).text, varibles::mainMenu.UIList);

    Button butLoc(&clic, But::MainB::bot, sf::IntRect(285, 300, 230, 90), spriteBut, TextElem(L"bot", sf::Vector2f(), font, 0, sf::Color(255, 25, 35), 25).text, varibles::mainMenu.UIList);

    Button butBot(&clic, But::MainB::localB, sf::IntRect(542, 300, 230, 90), spriteBut, TextElem(L"local", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, varibles::mainMenu.UIList);
    
    //-------[local]

    //create the input sprite
    SprElement sprInp("image/main/inputBackground.png");
    sf::Sprite spriteInp = sprInp.sprite;

    //create the button sprite
    SprElement sprBut2("image/localMenu/start.png");
    sf::Sprite spriteBut2 = sprBut2.sprite;

    TextElem SelectNamesLine1(L"select the names of the players", sf::Vector2f(610, 70), font, &varibles::startLocal.UIList, sf::Color(0, 166, 251), 25);
    TextElem SelectNamesLine2(L"in the game", sf::Vector2f(610, 97), font, &varibles::startLocal.UIList, sf::Color(0, 166, 251), 25);

    SprElement nameBacking("image/localMenu/backing.png", sf::Vector2f(200, 300), &varibles::startLocal.UIList);

    NameInput nameInp0(&inputChar, &clic, spriteInp, sf::IntRect(62, 57, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 0);

    NameInput nameInp1(&inputChar, &clic, spriteInp, sf::IntRect(62, 142, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 1);

    NameInput nameInp2(&inputChar, &clic, spriteInp, sf::IntRect(62, 227, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 2);

    NameInput nameInp3(&inputChar, &clic, spriteInp, sf::IntRect(62, 312, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 3);

    NameInput nameInp4(&inputChar, &clic, spriteInp, sf::IntRect(62, 397, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 4);

    NameInput nameInp5(&inputChar, &clic, spriteInp, sf::IntRect(62, 482, 275, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpName::localB::inpName, varibles::startLocal.UIList, 5);

    Button localStartButton(&clic, But::localB::start, sf::IntRect(440, 483, 275, 60), spriteBut2, TextElem(L"start", sf::Vector2f(), font, 0, sf::Color(5, 130, 202), 25).text, varibles::startLocal.UIList);

    //-------[localGame]
    //create the input sprite
    SprElement localGamesprInp("image/localGameMenu/mainInputInLocal.png");
    sf::Sprite localGamespriteInp = localGamesprInp.sprite;

    //create the button sprite
    SprElement sprHintBut("image/localGameMenu/butLocalGame.png");
    sf::Sprite spriteHintBut = sprHintBut.sprite;

    //create the output sprite
    SprElement localGamesprOut("image/localGameMenu/localOutput.png");
    sf::Sprite localGamespriteOut = localGamesprOut.sprite;

    TextElem NameLocalGame(L"Word the game: Local", sf::Vector2f(400, 50), font, &varibles::localGame.UIList, sf::Color(0, 166, 251), 35);

    Output mainOutputInLocalGame(localGamespriteOut, TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 130, 202), 25).text, sf::Vector2f(400, 285), sf::Vector2i(28, 20), Out::localGame::lineChec, varibles::localGame.UIList);

    InputInOutput mainInputLocalGame(&inputChar, &clic, localGamespriteInp, sf::IntRect(36, 510, 410, 60), TextElem(L"", sf::Vector2f(), font, 0, sf::Color(5, 25, 35), 25).text, InpInOut::localB::inpLocalGame, varibles::localGame.UIList, &mainOutputInLocalGame);

    std::vector<Element*> elem = { &mainInputLocalGame, &mainOutputInLocalGame };

    Button hint(&clic, But::LocalGameB::hint, sf::IntRect(483, 510, 281, 60), spriteHintBut, TextElem(L"hint", sf::Vector2f(), font, 0, sf::Color(5, 130, 202), 25).text, varibles::localGame.UIList, &elem);

    //-------[end]



    //-------[]

    varibles::nowElements = &varibles::mainMenu;

    while (window.isOpen())
    {
        clic = 0;

        sf::Event event;
        while (window.pollEvent(event))
        {
            std::string str;

            if (event.type == sf::Event::TextEntered)
            {
                    inputChar = (wchar_t)(event.key.code);
            }
                
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                clic = 1;
        }

        window.clear(sf::Color(5, 25, 35));

        for (int i = 0; i < (*varibles::nowElements).UIList.size(); i++)
        {
            (*varibles::nowElements).UIList[i]->handle(window);
        }

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