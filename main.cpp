#include <iostream>
#include <string>
#include <locale>
#include <userIO.h>
#include <command.h>

int main()
{
    std::setlocale(LC_ALL, "ko_KR.UTF-8");

    // file diagnosis

    while (true)
    {
        std::wstring userInput = getUserInput();
        switch (cmdType(userInput))
        {
        case HELP:
            help(userInput);
            break;
        case ADD:
            printSysMsg(L"ADD");
            break;
        case DEL:
            printSysMsg(L"DEL");
            break;
        case SEARCH:
            printSysMsg(L"SEARCH");
            break;
        case QUIT:
            printSysMsg(L"QUIT");
            break;
        default:
            break;
        }
    }

    return 0;
}