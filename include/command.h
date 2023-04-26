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

void help(std::wstring);
void add(std::wstring);
void del(std::wstring);
void search(std::wstring);
bool quit(std::wstring);