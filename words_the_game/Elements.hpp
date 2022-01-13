#pragma once
#include <iostream>
#include <thread>
#include "SFML/Graphics.hpp"

struct InputWord
{
    std::wstring str;

    bool systemMessage = 0;
};

class Element
{
public:
    virtual void handle(sf::RenderWindow& window)
    {
        draw(window);
    }
    virtual void draw(sf::RenderWindow& window) = 0;
};

class Output : public Element
{
public:
    Output(sf::Sprite spr, sf::Text text, sf::Vector2f pos, sf::Vector2i indent, bool(*fun)(InputWord& input, std::wstring previousStr), std::vector <Element*>& UIList);

    void draw(sf::RenderWindow& window);

    void changeLine(std::wstring spr);

    void addLine(std::wstring spr);

    sf::Sprite spr;
    sf::Text example;
    std::vector<InputWord> text{ InputWord{L""} };

private:
    bool(*fun)(InputWord& input, std::wstring previousStr);
    void setTextOrigin(sf::Text& example);
    void setTextPosition(sf::Text& example, sf::Sprite spr, sf::Vector2i indent);
};

class Input : public Element
{
public:
    Input(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring), std::vector <Element*>& UIList);
    
    virtual void handle(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool choice = 0;
    void(*fun)(std::wstring);
    sf::IntRect rect;
    sf::Sprite spr;
    sf::Text text;


protected:
    void begineInput();
    virtual void endInput();
    void centringText();
    void backspace();
    void addLetter();

    wchar_t* inputChar;
    bool* clic;
};

class NameInput : public Input
{
public:
    NameInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring, uint8_t), std::vector <Element*>& UIList, uint8_t index);

    void(*fun)(std::wstring, uint8_t index);
    void endInput();

protected:

private:
    uint8_t index;
};

class InputInOutput : public Input
{
public:
    InputInOutput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring, Output*), std::vector <Element*>& UIList, Output* out);

    void handle(sf::RenderWindow& window);
    void(*fun)(std::wstring, Output*);
    void endInput();

protected:

private:
    Output* out;
};

class Button : public Element
{
public:
    Button(bool* clic, void(*funBut)(std::vector <Element*>*), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text textBut, std::vector <Element*>& UIList, std::vector <Element*>* object = 0);

    Button(bool* clic, void(*funBut)(std::vector <Element*>*), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text* textBut, std::vector <Element*>& UIList, std::vector <Element*>* object = 0);

    void handle(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);

    void(*funBut)(std::vector <Element*>*);
    sf::IntRect rectBut;
    sf::Sprite spriteBut;
    sf::Text textBut;

private:
    std::vector <Element*>* object;
    bool* clic;
};

class SprElement : public Element
{
public:
    SprElement(sf::Sprite& dr);
    SprElement(std::string path, sf::Vector2f pos = sf::Vector2f(), std::vector <Element*>* UIList = 0);
    void draw(sf::RenderWindow& window);

    sf::Texture tex;
    sf::Sprite sprite;
};

class TextElem : public Element
{
public:
    TextElem(sf::Text& dr);
    TextElem(std::wstring str, sf::Vector2f pos, sf::Font& font, std::vector <Element*>* UIElement = 0, sf::Color col = sf::Color(0, 166, 251), int scale = 25);
    void draw(sf::RenderWindow& window);

    sf::Text text;
};