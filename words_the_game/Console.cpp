#include "Console.hpp"

namespace console
{
    int chat = 0;
    char exceptionLitter[] = { '�', '�', '�', '�' };


    void dictionary()
    {
        std::string line;

        std::ifstream mainText("russian_nouns.txt"); // �������� ���� ��� ������ (https://harrix.dev/blog/2018/russian-nouns/)

        if (mainText.is_open())
        {
            while (getline(mainText, line))
            {
                auto it = varibles::words.find(line[0]);

                if (it == varibles::words.end())
                {
                    std::vector<std::string> a = { line };
                    varibles::words.emplace(line[0], a);
                }
                else
                {
                    it->second.push_back(line);
                }
            }
        }
        else
        {
            std::cout << "unable to open the file :: you may have forgotten to inst call the dictionary \"russian_nouns\"\n";
        }
        mainText.close();     // ��������� ����
    }

    bool existence�heck(std::string wordIn)
    {
        std::vector<std::string>& charWords = varibles::words[wordIn[0]];

        for (int i = 0; i < charWords.size(); i++)
        {
            if (charWords[i] == wordIn)
            {
                chat = i;
                return 1;
            }
        }
        return 0;
    }

    void eliminator(std::string& word)
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

    void bot()
    {
        srand(clock());

        system("cls");
        std::string wordIn;
        std::cin >> wordIn;
        bool losing = 0;
        bool start = 1;

        char buffer = wordIn[0];

        do
        {
            if (existence�heck(wordIn))
            {
                eliminator(wordIn);
                if (buffer == wordIn[0] || start)
                {
                    start = 0;
                    std::vector<std::string>& charWords = varibles::words[wordIn[wordIn.size() - 1]];

                    int i = (rand() + 1) % (charWords.size() + 1) - 1;
                    std::cout << "bot>" << charWords[i] << std::endl;

                    eliminator(charWords[i]);

                    buffer = charWords[i][charWords[i].size() - 1];
                    charWords.erase(charWords.begin() + i);
                }
                else
                    std::cout << "<!>��� ������\n";
            }
            else
                std::cout << "<!>������ ����� ��� ��� ��� ���� ������������\n";
            std::cin >> wordIn;

        } while (!losing);
        std::cout << "�� �������!";
    }

    void defolt(std::string wordIn, std::vector<std::string> name)
    {
        bool start = 1;
        int b = 0;
        char buffer = '\0';
        do
        {
            if (existence�heck(wordIn))
            {
                eliminator(wordIn);
                if (buffer == wordIn[0] || start)
                {
                    start = 0;
                    b = b == name.size() - 1 ? 0 : b + 1;
                    varibles::words[wordIn[0]].erase(varibles::words[wordIn[0]].begin() + chat);
                    std::cout << name[b] << '>';
                    buffer = wordIn[wordIn.size() - 1];
                }
                else
                    std::cout << "<!>��� ������\n" << name[b] << '>';
            }
            else
                std::cout << "<!>������ ����� ��� ��� ��� ���� ������������\n" << name[b] << '>';

            std::cin >> wordIn;

        } while (wordIn != "exit");
    }

    void consolStart()
    {

        console::dictionary();
        std::cout << '#';
        std::string wordIn;
        std::cin >> wordIn;
        if (wordIn == "bot")
            console::bot();
        else if (wordIn[0] >= 50 && wordIn[0] <= 57)
        {
            char defoltNames[] = { '*', '#', '$', '&', '@', '?', 'A', 'B', 'C' };
            std::vector<std::string> localName;
            for (uint8_t i = 0; i < wordIn[0] - 48; i++)
            {
                std::string nowName;
                std::cin >> nowName;

                if (nowName == "0")
                {
                    int k = 0;

                    for (int i = 0; i < localName.size(); i++)
                    {
                        for (int di = 0; di < 9; di++)
                        {
                            std::string str = { defoltNames[di] };
                            if (localName[i] == str)
                                k += k == 9 ? -9 : 1;

                        }
                    }

                    nowName = defoltNames[i + k];
                }

                localName.push_back(nowName);
            }
            system("cls");
            std::cout << localName[0] << '>';
            std::cin >> wordIn;
            console::defolt(wordIn, localName);
        }
        else
            console::defolt(wordIn, { "*", "#" });
    }
}