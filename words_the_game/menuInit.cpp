#include "menu.hpp"
#include "Font.hpp"
#include "Variable.hpp"
#include "Elements.hpp"
#include "FunctionForElement.hpp"
#include "Localization.h"

Font font("C:/WINDOWS/Fonts/arial.ttf");

SprElement sprBut("image/main/but.png");

SprElement sprInp("image/main/inputBackground.png");

SprElement sprBut2("image/localMenu/start.png");

sf::Text textTemplateForInputName = TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).phraze;

SprElement localGamesprInp("image/localGameMenu/mainInputInLocal.png");

SprElement sprHintBut("image/localGameMenu/butLocalGame.png");

SprElement localGamesprOut("image/localGameMenu/localOutput.png");

SprElement changeLanguage("image/mainMenu/language.png");

namespace varibles
{

    namespace menu
    {
        Menu mainMenu
        ({

            new SprElement{"image/mainMenu/backing.png", sf::Vector2f(400, 300)},

            new TextElem{L"gameName", sf::Vector2f(400, 150), font, sf::Color(0, 166, 251), 35},

            new Button{&varibles::Input::clic, But::MainB::online, sf::IntRect(27, 300, 230, 90), sprBut.sprite, TextElem(L"online", sf::Vector2f(), font, sf::Color(255, 25, 35), 25).phraze},

            new Button{&varibles::Input::clic, But::MainB::bot, sf::IntRect(285, 300, 230, 90), sprBut.sprite, TextElem(L"bot", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).phraze},

            new Button{&varibles::Input::clic, But::MainB::localB, sf::IntRect(542, 300, 230, 90), sprBut.sprite, TextElem(L"local", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).phraze},

            new Button{&varibles::Input::clic, But::MainB::changeLanguage, sf::IntRect(368, 438, 63, 63), changeLanguage.sprite, TextElem(L"language", sf::Vector2f(0, 55), font, sf::Color(0, 166, 251), 15).phraze},
            }),

            startLocal
            ({
                new TextElem {L"suggestions for entering a name : 1", sf::Vector2f(580, 70), font, sf::Color(0, 166, 251), 25},
                new TextElem {L"suggestions for entering a name : 2", sf::Vector2f(580, 97), font, sf::Color(0, 166, 251), 25},

                new SprElement {"image/localMenu/backing.png", sf::Vector2f(200, 300)},

                new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 57, 275, 60), textTemplateForInputName, InpName::localB::inpName, 0},

                new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 142, 275, 60), textTemplateForInputName, InpName::localB::inpName, 1},

                new NameInput { &varibles::Input::inputChar,&varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 227, 275, 60), textTemplateForInputName, InpName::localB::inpName, 2},

                new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 312, 275, 60), textTemplateForInputName, InpName::localB::inpName, 3},

                new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 397, 275, 60), textTemplateForInputName, InpName::localB::inpName, 4},

                new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 482, 275, 60), textTemplateForInputName, InpName::localB::inpName, 5},

                new Button {&varibles::Input::clic, But::localB::start, sf::IntRect(440, 483, 275, 60), sprBut2.sprite, TextElem(L"start", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).phraze}
                }),

            localGame
            ({
                new TextElem {L"gameName:local", sf::Vector2f(400, 50), font, sf::Color(0, 166, 251), 35},
                new Output{localGamesprOut.sprite, TextElem(L"", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).phraze, sf::Vector2f(400, 285), sf::Vector2i(28, 20), Out::localGame::lineChec},

                new ContinuousInput{ &varibles::Input::inputChar, &varibles::Input::clic, localGamesprInp.sprite, sf::IntRect(36, 510, 410, 60), TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).phraze, InpInOut::localB::inpLocalGame},

                new Button{&varibles::Input::clic, But::LocalGameB::hint, sf::IntRect(483, 510, 281, 60), sprHintBut.sprite, TextElem(L"hit", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).phraze}
                }),

            BotGame
            ({
                new TextElem {L"gameName:bot", sf::Vector2f(400, 50), font, sf::Color(0, 166, 251), 35},
                new Output{localGamesprOut.sprite, TextElem(L"", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).phraze, sf::Vector2f(400, 285), sf::Vector2i(28, 20), Out::botGame::lineChec},

                new ContinuousInput{ &varibles::Input::inputChar, &varibles::Input::clic, localGamesprInp.sprite, sf::IntRect(36, 510, 410, 60), TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).phraze, InpInOut::Bot::inpLocalGame},

                new Button{&varibles::Input::clic, But::BotGameB::hint, sf::IntRect(483, 510, 281, 60), sprHintBut.sprite, TextElem(L"hit", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).phraze}

                });
    }
}