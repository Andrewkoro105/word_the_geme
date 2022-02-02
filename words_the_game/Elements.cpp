#include "Elements.hpp"


//---------[Output]

Output::Output(sf::Sprite spr, sf::Text example, sf::Vector2f pos, sf::Vector2i indent, bool(*fun)(InputWord& input, std::wstring previousStr)) : fun(fun)
{
    spr.setPosition(pos);
    this->spr = spr;

    setTextOrigin(example);
    setTextPosition(example, spr, indent);


    this->example = example;
}

void Output::draw(sf::RenderWindow& window)
{
    window.draw(spr);

    sf::Text nowText = example;

    for (int i = phraze.size() - 1; i >= 0; i--)
    {
        nowText.setString(phraze[i].str);

        window.draw(nowText);

        nowText.setPosition(nowText.getPosition() - sf::Vector2f(0, 35));
    }
}

void Output::changeLine(std::wstring str, bool check)
{
    InputWord word{ str };

    if (!check || fun(word, phraze[phraze.size() - 2].str))
        phraze[phraze.size() - 1] = word;
}

void Output::addLine(std::wstring str, bool check)
{
    if (phraze.size() >= 11)
        phraze.erase(phraze.begin());

    InputWord word { str };

    if (!check || fun(word, phraze[phraze.size() - 1].str))
        phraze.push_back(word);
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

Input::Input(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring)) : clic(clic), rect(rect), fun(fun), inputChar(inputChar)
{
    spr.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    this->spr = spr;

    phraze.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    this->phraze = phraze;
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
    window.draw(phraze);
}

void Input::setInput(std::wstring text)
{
    phraze.setString(text);

    sf::FloatRect textRect = phraze.getLocalBounds();
    phraze.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    
    phraze.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

void Input::begineInput()
{
            choice = 1;
}

void Input::endInput()
{
    choice = 0;
    fun(phraze.getString());
}

void Input::centringText()
{
    sf::FloatRect textRect = phraze.getLocalBounds();
    phraze.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
}

void Input::addLetter()
{
    phraze.setString((std::wstring)phraze.getString() + (wchar_t)*inputChar);

    *inputChar = '\0';
}

void Input::backspace()
{
    std::wstring nowtext = (std::wstring)phraze.getString();
    nowtext.pop_back();
    phraze.setString(nowtext);
    *inputChar = '\0';
}

//---------[NameInput]

NameInput::NameInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring, uint8_t), uint8_t index) :
    Input(inputChar, clic, spr, rect, phraze, 0), fun(fun), index(index) {}

void NameInput::endInput()
{
    choice = 0;
    fun(phraze.getString(), index);
}

//---------[InputInOutput]
ContinuousInput::ContinuousInput(wchar_t* inputChar, bool* clic, sf::Sprite spr, sf::IntRect rect, sf::Text phraze, void (*fun)(std::wstring)) :
    Input(inputChar, clic, spr, rect, phraze, 0), fun(fun), out(out) 
{
    choice = 1;
}

void ContinuousInput::handle(sf::RenderWindow& window)
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

void ContinuousInput::endInput()
{ 
    fun(phraze.getString());
    phraze.setString(L"");
}
//---------[Button]

Button::Button(bool* clic, void(*funBut)(), sf::IntRect rectBut, sf::Sprite spriteBut, sf::Text phrazeBut) :
    clic(clic), funBut(funBut), rectBut(rectBut), textBut(phrazeBut)
{
    spriteBut.setOrigin(spriteBut.getTextureRect().width / 2, spriteBut.getTextureRect().height / 2);
    spriteBut.setPosition(rectBut.left + rectBut.width / 2, rectBut.top + rectBut.height / 2);

    this->spriteBut = spriteBut;
}

void Button::localiztion()
{
    if (renderText.getString() != localization.getPhrase(textBut.getString()))
    {
        renderText = textBut;
        renderText.setString(localization.getPhrase(textBut.getString()));

        sf::FloatRect textRect = renderText.getLocalBounds();
        renderText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        
        renderText.setPosition(rectBut.left + rectBut.width / 2 + textBut.getPosition().x, rectBut.top + rectBut.height / 2 + textBut.getPosition().y);
    }
}

void Button::handle(sf::RenderWindow& window)
{
    localiztion();

    draw(window);

    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

    if (*clic && (rectBut.left < x && rectBut.left + rectBut.width > x &&
        rectBut.top < y && rectBut.top + rectBut.height > y))
        funBut();
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(spriteBut);
    window.draw(renderText);
}

//---------[SprElement]

SprElement::SprElement(sf::Sprite& sprite)
{
    tex = *sprite.getTexture();
    sprite.setTexture(tex);

    this->sprite = sprite;
}

SprElement::SprElement(std::string path, sf::Vector2f pos)
{
    tex.loadFromFile(path);
    sf::Sprite spr(tex);

    sf::IntRect texRect = spr.getTextureRect();
    spr.setOrigin(texRect.left + texRect.width / 2.0f,
        texRect.top + texRect.height / 2.0f);
    spr.setPosition(pos);

    sprite = spr;
}

void SprElement::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

//---------[TextElem]

TextElem::TextElem(sf::Text& phraze) : phraze(phraze) {}

TextElem::TextElem(sf::Text& phraze, sf::Vector2f pos)
{
    sf::FloatRect textRect = phraze.getLocalBounds();
    phraze.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    phraze.setPosition(pos);

    this->phraze = phraze;
}

TextElem::TextElem(std::wstring str, sf::Vector2f pos, Font& font, sf::Color col, int scale)
{
    sf::Text phraze(str, font);
    phraze.setCharacterSize(scale);
    phraze.setFillColor(col);
    sf::FloatRect textRect = phraze.getLocalBounds();
    phraze.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    phraze.setPosition(pos);

    this->phraze = phraze;
}

void TextElem::localiztion()
{
    if (renderText.getString() != localization.getPhrase(phraze.getString()))
    {
        renderText = phraze;
        renderText.setString(localization.getPhrase(phraze.getString()));

        sf::FloatRect textRect = renderText.getLocalBounds();
        renderText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        if (phraze.getPosition() == sf::Vector2f())
            renderText.setPosition(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
        else
            renderText.setPosition(phraze.getPosition());
    }
}

void TextElem::handle(sf::RenderWindow& window)
{
    localiztion();

    draw(window);
}

void TextElem::draw(sf::RenderWindow& window)
{
    window.draw(renderText);
}