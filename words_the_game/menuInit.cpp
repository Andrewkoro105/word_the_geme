#include "menu.hpp"
#include "Font.hpp"
#include "Variable.hpp"
#include "Elements.hpp"
#include "FunctionForElement.hpp"

Font font("C:/WINDOWS/Fonts/arial.ttf");

SprElement sprBut("image/main/but.png");

SprElement sprInp("image/main/inputBackground.png");

SprElement sprBut2("image/localMenu/start.png");

sf::Text textTemplateForInputName = TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).text;

SprElement localGamesprInp("image/localGameMenu/mainInputInLocal.png");

SprElement sprHintBut("image/localGameMenu/butLocalGame.png");

SprElement localGamesprOut("image/localGameMenu/localOutput.png");


Output mainOutputInLocalGame{ localGamesprOut.sprite, TextElem(L"", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).text, sf::Vector2f(400, 285), sf::Vector2i(28, 20), Out::localGame::lineChec };

InputInOutput mainInputLocalGame{ &varibles::Input::inputChar, &varibles::Input::clic, localGamesprInp.sprite, sf::IntRect(36, 510, 410, 60), TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).text, InpInOut::localB::inpLocalGame};


namespace varibles
{
    Menu mainMenu
    ({

        new SprElement{"image/mainMenu/backing.png", sf::Vector2f(400, 300)},

        new TextElem{L"Word the game", sf::Vector2f(400, 150), font, sf::Color(0, 166, 251), 35},

        new Button{&varibles::Input::clic, But::MainB::online, sf::IntRect(27, 300, 230, 90), sprBut.sprite, TextElem(L"online", sf::Vector2f(), font, sf::Color(255, 25, 35), 25).text},

        new Button{&varibles::Input::clic, But::MainB::bot, sf::IntRect(285, 300, 230, 90), sprBut.sprite, TextElem(L"bot", sf::Vector2f(), font, sf::Color(255, 25, 35), 25).text},

        new Button{&varibles::Input::clic, But::MainB::localB, sf::IntRect(542, 300, 230, 90), sprBut.sprite, TextElem(L"local", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).text},
    }),

    startLocal
    ({
        new TextElem {L"select the names of the players", sf::Vector2f(610, 70), font, sf::Color(0, 166, 251), 25},
        new TextElem {L"in the game", sf::Vector2f(610, 97), font, sf::Color(0, 166, 251), 25},

        new SprElement {"image/localMenu/backing.png", sf::Vector2f(200, 300)},

        new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 57, 275, 60), textTemplateForInputName, InpName::localB::inpName, 0},

        new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 142, 275, 60), textTemplateForInputName, InpName::localB::inpName, 1},

        new NameInput { &varibles::Input::inputChar,&varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 227, 275, 60), textTemplateForInputName, InpName::localB::inpName, 2},

        new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 312, 275, 60), textTemplateForInputName, InpName::localB::inpName, 3},

        new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 397, 275, 60), textTemplateForInputName, InpName::localB::inpName, 4},

        new NameInput {&varibles::Input::inputChar, &varibles::Input::clic, sprInp.sprite, sf::IntRect(62, 482, 275, 60), textTemplateForInputName, InpName::localB::inpName, 5},

        new Button {&varibles::Input::clic, But::localB::start, sf::IntRect(440, 483, 275, 60), sprBut2.sprite, TextElem(L"start", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).text}
    }),

    localGame
    ({
        new TextElem {L"Word the game: Local", sf::Vector2f(400, 50), font, sf::Color(0, 166, 251), 35},
        new Output{localGamesprOut.sprite, TextElem(L"", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).text, sf::Vector2f(400, 285), sf::Vector2i(28, 20), Out::localGame::lineChec},

        new InputInOutput{ &varibles::Input::inputChar, &varibles::Input::clic, localGamesprInp.sprite, sf::IntRect(36, 510, 410, 60), TextElem(L"", sf::Vector2f(), font, sf::Color(5, 25, 35), 25).text, InpInOut::localB::inpLocalGame},

        new Button{&varibles::Input::clic, But::LocalGameB::hint, sf::IntRect(483, 510, 281, 60), sprHintBut.sprite, TextElem(L"hint", sf::Vector2f(), font, sf::Color(5, 130, 202), 25).text}
    });
}