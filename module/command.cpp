#include <command.h>
#include <userIO.h>

Cmd cmdType(std::wstring userInput)
{
    std::wstring cmd = stepStr(userInput, 0, PURE);

    if (cmd.compare(L"add") == 0)
        return ADD;
    if (cmd.compare(L"delete") == 0)
        return DEL;
    if (cmd.compare(L"search") == 0)
        return SEARCH;
    if (cmd.compare(L"quit") == 0)
        return QUIT;

    return HELP;
}