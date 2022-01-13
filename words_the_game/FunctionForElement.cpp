
#include "FunctionForElement.hpp"

namespace LocalGame
{
    wchar_t exceptionLitter[] = { L'ь', L'ъ', L'й', L'ы' };
    extern int id = 0;


    int existenceСheck(std::wstring wordIn) // 0 -> does not exist  | 1 -> existence | 2 -> already used
    {
        std::vector<word>& charWords = varibles::grWords[wordIn[0]];

        for (int i = 0; i < charWords.size(); i++)
        {
            if (charWords[i].str == wordIn)
            {
                if (charWords[i].existence)
                {
                    charWords[i].existence = 0;
                    return 1;
                }
                else
                    return 2;
            }
        }
        return 0;
    }

    void eliminator(std::wstring& word)
    {
        for (int i = 0; i < word.size(); i++)
        {
            for (int ei = 0; ei < 4; ei++)
            {
                if (word[i] == exceptionLitter[ei])
                    word.erase(i, 1);
            }
        }
    }

    void defoltOutput(InputWord& str)
    {
        str.str = varibles::names[id].name + L" > " + str.str;
        str.systemMessage = 0;
        id++;
        if (id == varibles::names.size())
            id = 0;
    }

    bool MainLocalGame(InputWord& str, std::wstring previousStr)
    {
        std::wstring nullStr = L"";
        switch (existenceСheck(str.str))
        {
        case 0:
            str.str = L"<!> такого слова нет";
            str.systemMessage = 1;
            break;
        case 1:
            eliminator(previousStr);

            if (str.str[0] == previousStr[previousStr.size() - 1] || previousStr == nullStr)
                defoltOutput(str);
            else
            {
                str.str = L"<!> это не по правилам";
                str.systemMessage = 1;
            }
            break;
        case 2:
            str.str = L"<!> это слово уже было";
            str.systemMessage = 1;
            break;
        }
        return 1;
    }
}

namespace But
{
    namespace localB
    {
        void start(std::vector <Element*>*)
        {
            std::vector<Player> nowPlayer;

            for (int i = 0; i < 6; i++)
                if (varibles::names[i].name != L"")
                    nowPlayer.push_back(varibles::names[i]);
            if (nowPlayer.size() >= 2)
            {
                varibles::names = nowPlayer;

                varibles::nowElements = &varibles::localGame;
            }
        }
    }
    namespace MainB
    {
        void localB(std::vector <Element*>*)
        {
            varibles::nowElements = &varibles::startLocal;
            std::cout << "local\n";
        }

        void bot(std::vector <Element*>*)
        {
            std::cout << "bot\n";
        }

        void online(std::vector <Element*>*)
        {
            std::cout << "online\n";
        }
    }
    namespace LocalGameB
    {
        void hint(std::vector <Element*>* elem)
        {
            std::vector<InputWord> textOut = dynamic_cast<Output*>((*elem)[1])->text;

            if (!(textOut.size() == 1 || (textOut.size() == 2 && textOut[1].systemMessage)))
            {

                std::wstring lustStr = textOut[textOut.size() - 1].systemMessage ? textOut[textOut.size() - 2].str : textOut[textOut.size() - 1].str;

                LocalGame::eliminator(lustStr);

                wchar_t lustChar = lustStr[lustStr.size() - 1];

                std::vector <std::wstring> unusedWords;



                for (int i = 0; i < varibles::grWords[lustChar].size(); i++)
                    if (varibles::grWords[lustChar][i].existence)
                        unusedWords.push_back(varibles::grWords[lustChar][i].str);

                if (unusedWords.size())
                    dynamic_cast<InputInOutput*>((*elem)[0])->text.setString(unusedWords[((rand() + 1) % (unusedWords.size()))]);

            }
        }
    }
}

namespace InpName
{
    namespace localB
    {
        void inpName(std::wstring str, uint8_t index)
        {
            varibles::names[index].name = str;
        }
    }
}

namespace InpInOut
{
    namespace localB
    {
        void inpLocalGame(std::wstring str, Output* out)
        {
            std::wcout << str << std::endl;

            if (out->text[out->text.size() - 1].systemMessage)
                out->changeLine(str);
            else
                out->addLine(str);
        }
    }
}

namespace Inp
{
    namespace localB
    {
        void inp(std::wstring str)
        {
            std::wcout << str << std::endl;
        }
    }
}

namespace Out
{
    namespace localGame
    {

        bool lineChec(InputWord& str, std::wstring previousStr)
        {
            return LocalGame::MainLocalGame(str, previousStr);
        }

    }
}
