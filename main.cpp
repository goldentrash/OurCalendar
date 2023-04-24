#include <iostream>
#include <string>
#include <locale>
#include <userIO.h>
#include <command.h>
#include <task.h>

int main()
{
    std::locale::global(std::locale("ko_KR.UTF-8"));

    readTasks(); // 무결성 검사

    printSysMsg(L"Welcom!");
    while (true)
    {
        std::wstring userInput = getUserInput();
        switch (cmdType(userInput))
        {
        case HELP:
            help(userInput);
            break;
        case ADD:
            add(userInput);
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