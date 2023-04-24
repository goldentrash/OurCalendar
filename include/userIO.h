#include <string>

enum StringType
{
    NORMAL,
    PURE,
    SPACE,
    BOOL,
    SPECIAL,
    DATE,
    NUM,
    ERROR
};

void printSysMsg(std::wstring);
std::wstring getUserInput();
std::wstring stepStr(std::wstring, int, StringType);
int dateCompare(std::wstring, std::wstring);