#pragma once
#include <iostream>
#include "Variable.hpp"

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
        void start(std::vector <Element*>*);
    }
    namespace MainB
    {
        void localB(std::vector <Element*>*);
        void bot(std::vector <Element*>*);
        void online(std::vector <Element*>*);
    }
    namespace LocalGameB
    {
        void hint(std::vector <Element*>* elem);
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
        void inpLocalGame(std::wstring str, Output* out);
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
}