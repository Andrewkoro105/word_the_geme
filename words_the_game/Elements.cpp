#include "Elements.hpp"


//---------[Output]

Output::Output(sf::Sprite spr, sf::Text example, sf::Vector2f pos, sf::Vector2i indent, bool(*fun)(InputWord& input, std::wstring previousStr), std::vector <Element*>& UIList) : fun(fun)
{
    spr.setPosition(pos);
    this->spr = spr;

    setTextOrigin(example);
    setTextPosition(example, spr, indent);


    this->example = example;


    UIList.push_back(this);
}

void Output::draw(sf::RenderWindow& window)
{
    window.draw(spr);

    sf::Text nowText = example;

    for (int i = text.size() - 1; i >= 0; i--)
    {
        nowText.setString(text[i].str);

        window.draw(nowText);

        nowText.setPosition(nowText.getPosition() - sf::Vector2f(0, 35));
    }
}

void Output::changeLine(std::wstring str)
{
    InputWord word{ str };

    if (fun(word, text[text.size() - 2].str))
        text[text.size() - 1] = word;
}

void Output::addLine(std::wstring str)
{
    if (text.size() >= 11)
        text.erase(text.begin());

    InputWord word { str };

    if (fun(word, text[text.size() - 1].str))
        text.push_back(word);
}

void Output::setTextOrigin(sf::Text& example)
{
    example.setString("A");

    sf::FloatRect textRect = example.getLocalBounds();
    example.setOrigin(textRect.left, textRect.top + textRect.height);
}

void Output::setTextPosition(sf::Text& example, sf::Sprite spr, sf::Vector2i indent)
{
    sf::IntRect sprRect = spr.getTextureRect();
    sprRect.left = spr.getPosition().x;
    sprRect.top = spr.getPosition().y;
    example.setPosition(sprRect.left - sprRect.width / 2 + indent.x, sprRect.top + sprRect.height / 2 - indent.y);
}

//---------[Input]

Input::Input(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring), std::vector <Element*>& UIList) : clic(clic), rect(rect), fun(fun), inputChar(inputChar)
{
    spr.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    this->spr = spr;

    text.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    this->text = text;

    UIList.push_back(this);
}

void Input::handle(sf::RenderWindow& window)
{
    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

    if (choice)
    {
        if (*inputChar == '\b')
        {
            backspace();

            centringText();
        }
        else if (*inputChar == ((wchar_t)'\n' + 3))//enter in wchar 3 more then in char
        {
            endInput();

            *inputChar = '\0';
        }
        else if (*inputChar != '\0')
        {
            addLetter();

            centringText();
        }



        if (*clic && (rect.left > x || rect.left + rect.width < x ||
            rect.top > y || rect.top + rect.height < y))
            endInput();
    }
    else
        if (*clic && (rect.left < x && rect.left + rect.width > x &&
            rect.top < y && rect.top + rect.height > y))
            begineInput();
    draw(window);
}

void Input::draw(sf::RenderWindow& window)
{
    window.draw(spr);
    window.draw(text);
}

void Input::begineInput()
{
            choice = 1;
}

void Input::endInput()
{
    choice = 0;
    fun(text.getString());
}

void Input::centringText()
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
}

void Input::addLetter()
{
    text.setString((std::wstring)text.getString() + (wchar_t)*inputChar);

    *inputChar = '\0';
}

void Input::backspace()
{
    std::wstring nowtext = (std::wstring)text.getString();
    nowtext.pop_back();
    text.setString(nowtext);
    *inputChar = '\0';
}

//---------[NameInput]

NameInput::NameInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring, uint8_t), std::vector <Element*>& UIList, uint8_t index) :
    Input(inputChar, clic, spr, rect, text, 0, UIList), fun(fun), index(index) {}

void NameInput::endInput()
{
    choice = 0;
    fun(text.getString(), index);
}

//---------[InputInOutput]
InputInOutput::InputInOutput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text text, void (*fun)(std::wstring, Output*), std::vector <Element*>& UIList, Output* out) :
    Input(inputChar, clic, spr, rect, text, 0, UIList), fun(fun), out(out) 
{
    choice = 1;
}

void InputInOutput::handle(sf::RenderWindow& window)
{
    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

        if (*inputChar == '\b')
        {
            backspace();

            centringText();
        }
        else if (*inputChar == ((wchar_t)'\n' + 3))//enter in wchar 3 more then in char
        {
            endInput();

            *inputChar = '\0';
        }
        else if (*inputChar != '\0')
        {
            addLetter();

            centringText();
        }

    draw(window);
}

void InputInOutput::endInput()
{ 
    fun(text.getString(), out);
    text.setString(L"");
}
//---------[Button]

Button::Button(bool* clic, void(*funBut)(std::vector <Element*>*), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text textBut, std::vector <Element*>& UIList, std::vector <Element*>* object) :
    clic(clic), funBut(funBut), rectBut(rectBut), object(object)
{
    spriteBut.setOrigin(spriteBut.getTextureRect().width / 2, spriteBut.getTextureRect().height / 2);
    spriteBut.setPosition(rectBut.left + rectBut.width / 2, rectBut.top + rectBut.height / 2);

    this->spriteBut = spriteBut;

    textBut.setPosition(rectBut.left + rectBut.width / 2, rectBut.top + rectBut.height / 2);

    this->textBut = textBut;


    UIList.push_back(this);
}

Button::Button(bool* clic, void(*funBut)(std::vector <Element*>*), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text* textBut, std::vector <Element*>& UIList, std::vector <Element*>* object) :
    clic(clic), funBut(funBut), rectBut(rectBut), object(object)
{
    spriteBut.setOrigin(spriteBut.getTextureRect().width / 2, spriteBut.getTextureRect().height / 2);
    spriteBut.setPosition(rectBut.left + rectBut.width / 2, rectBut.top + rectBut.height / 2);

    this->spriteBut = spriteBut;

    (* textBut).setPosition(rectBut.left + rectBut.width / 2, rectBut.top + rectBut.height / 2);

    this->textBut = *textBut;


    UIList.push_back(this);
}

void Button::handle(sf::RenderWindow& window)
{
    draw(window);

    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

    if (*clic && (rectBut.left < x && rectBut.left + rectBut.width > x &&
        rectBut.top < y && rectBut.top + rectBut.height > y))
        funBut(object);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(spriteBut);
    window.draw(textBut);
}

//---------[SprElement]

SprElement::SprElement(sf::Sprite& sprite)
{
    tex = *sprite.getTexture();
    sprite.setTexture(tex);

    this->sprite = sprite;
}

SprElement::SprElement(std::string path, sf::Vector2f pos, std::vector <Element*>* UIList)
{
    tex.loadFromFile(path);
    sf::Sprite spr(tex);

    sf::IntRect texRect = spr.getTextureRect();
    spr.setOrigin(texRect.left + texRect.width / 2.0f,
        texRect.top + texRect.height / 2.0f);
    spr.setPosition(pos);

    sprite = spr;

    if (UIList != 0)
        (*UIList).push_back(this);
}

void SprElement::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

//---------[TextElem]

TextElem::TextElem(sf::Text& text) : text(text) {}

TextElem::TextElem(std::wstring str, sf::Vector2f pos, sf::Font& font, std::vector <Element*>* UIElement, sf::Color col, int scale)
{
    sf::Text text(str, font);
    text.setFillColor(col);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(pos);
    text.setCharacterSize(scale);

    this->text = text;

    if (UIElement != 0)
        (*UIElement).push_back(this);

}

void TextElem::draw(sf::RenderWindow& window)
{
    window.draw(text);
}