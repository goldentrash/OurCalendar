#include <iostream>
#include <string>
#include <locale>
#include <userIO.h>
#include <command.h>
#include <task.h>

int main()
{
    std::locale::global(std::locale("ko_KR.UTF-8")); // 한글 사용을 위한 locale 설정

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
            del(userInput);
            break;
        case SEARCH:
            search(userInput);
            break;
        case QUIT:
            quit(userInput);
            return 0;
        default:
            break;
        }
    }

    return 0;
}