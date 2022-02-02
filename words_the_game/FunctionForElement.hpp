#pragma once
#include <iostream>
#include "Variable.hpp"

namespace BotGame
{
    bool botMove();
    int existence—heck(std::wstring wordIn);
    void eliminator(std::wstring& word);
    void defoltOutput(InputWord& str);
    bool MainBotGame(InputWord& str, std::wstring previousStr);

    extern wchar_t exceptionLitter[];
}

namespace LocalGame
{
    int existence—heck(std::wstring wordIn);
    void eliminator(std::wstring& word);
    void defoltOutput(InputWord& str);
    bool MainLocalGame(InputWord& str, std::wstring previousStr);

    extern wchar_t exceptionLitter[];
    extern int id;
}

namespace But
{
    namespace localB
    {
        void start();
    }
    namespace MainB
    {
        void localB();
        void bot();
        void online();
        void changeLanguage();
    }
    namespace LocalGameB
    {
        void hint();
    }

    namespace BotGameB
    {
        void hint();
    }
}

namespace InpName
{
    namespace localB
    {
        void inpName(std::wstring str, uint8_t index);
    }
}

namespace InpInOut
{
    namespace localB
    {
        void inpLocalGame(std::wstring str);
    }
    namespace Bot
    {
        void inpLocalGame(std::wstring str);
    }
}

namespace Inp
{
    namespace localB
    {
        void inp(std::wstring str);
    }
}

namespace Out
{
    namespace localGame
    {
        bool lineChec(InputWord& str, std::wstring previousStr);
    }

    namespace botGame
    {
        bool lineChec(InputWord& str, std::wstring previousStr);
    }
}