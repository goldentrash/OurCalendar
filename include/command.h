#include <string>

enum Cmd
{
    HELP,
    ADD,
    DEL,
    SEARCH,
    QUIT
};

Cmd cmdType(std::wstring);