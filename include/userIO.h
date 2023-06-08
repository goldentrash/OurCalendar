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
    ERROR,
    DURATION_UNIT
};

void printSysMsg(std::wstring);
std::wstring getUserInput();
std::wstring stepStr(std::wstring, int, StringType);
int dateCompare(std::wstring, std::wstring);
std::wstring addDate(std::wstring, std::wstring, std::wstring);
std::wstring calcDateGap(std::wstring, std::wstring);