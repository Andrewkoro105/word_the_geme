#pragma once
#include <iostream>
#include <thread>
#include "Font.hpp"
#include "Localization.h"
#include "SFML/Graphics.hpp"

struct InputWord
{
    std::wstring str;

    bool systemMessage = 0;
};

class Element
{
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handle(sf::RenderWindow& window)
    {
        draw(window);
    }
};

class SprElement : public Element
{
public:
    SprElement(sf::Sprite& dr);
    SprElement(std::string path, sf::Vector2f pos = sf::Vector2f());
    void draw(sf::RenderWindow& window);

    sf::Sprite sprite;
private:
    sf::Texture tex;
};

class TextElem : public Element
{
public:
    TextElem(sf::Text& dr);
    TextElem(sf::Text& dr, sf::Vector2f pos);
    TextElem(std::wstring str, sf::Vector2f pos, Font& font, sf::Color col = sf::Color(0, 166, 251), int scale = 25);
    void handle(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    sf::Text phraze;
private:
    void localiztion();

    sf::Text renderText;
};

class Output : public Element
{
public:
    Output(sf::Sprite spr, sf::Text phraze, sf::Vector2f pos, sf::Vector2i indent, bool(*fun)(InputWord& input, std::wstring previousStr));

    void draw(sf::RenderWindow& window);

    void changeLine(std::wstring spr, bool check = 1);

    void addLine(std::wstring spr, bool check = 1);

    sf::Sprite spr;
    sf::Text example;
    std::vector<InputWord> phraze{ InputWord{L""} };

private:
    bool(*fun)(InputWord& input, std::wstring previousStr);
    void setTextOrigin(sf::Text& example);
    void setTextPosition(sf::Text& example, sf::Sprite spr, sf::Vector2i indent);
};

class Input : public Element
{
public:
    Input(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring));
    
    virtual void handle(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setInput(std::wstring text);

    bool choice = 0;
    void(*fun)(std::wstring);
    sf::IntRect rect;
    sf::Sprite spr;
    sf::Text phraze;


protected:
    void begineInput();
    void centringText();
    void backspace();
    void addLetter();
    virtual void endInput();

    //uint8_t countChar;
    wchar_t* inputChar;
    bool* clic;
};

class NameInput : public Input
{
public:
    NameInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring, uint8_t), uint8_t index);

    void(*fun)(std::wstring, uint8_t index);
    void endInput();

protected:

private:
    uint8_t index;
};

class ContinuousInput : public Input
{
public:
    ContinuousInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring));

    void handle(sf::RenderWindow& window);
    void(*fun)(std::wstring);
    void endInput();

private:
    Output* out;
};

class Button : public Element
{
public:
    Button(bool* clic, void(*funBut)(), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text phrazeBut = sf::Text());

    void handle(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void(*funBut)();
    sf::IntRect rectBut;
    sf::Sprite spriteBut;

    sf::Text textBut;
private:
    void localiztion();
    
    sf::Text renderText;
    bool* clic;
};
