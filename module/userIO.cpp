#include <userIO.h>
#include <iostream>

void printSysMsg(std::wstring msg)
{
    std::wcout << L"System: " << msg << std::endl;
}

std::wstring getUserInput()
{
    std::wstring userInput;
    std::wcout << "> ";
    std::getline(std::wcin, userInput);
    return userInput;
}

bool isKorChar(const wchar_t c)
{
    return (c >= L'가' && c <= L'힣') ||
           (c >= L'ㄱ' && c <= L'ㅣ') ||
           (c >= 0x1100 && c <= 0x1112) ||
           (c >= 0x1161 && c <= 0x1175) ||
           (c >= 0x11A8 && c <= 0x11C3);
};
bool isEngChar(const wchar_t c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
};
bool isSpaceChar(const wchar_t c)
{
    return c == '\t' || c == ' ';
};
bool isBoolChar(const wchar_t c)
{
    return c == 'Y' || c == 'N';
};
bool isSpecialChar(const wchar_t c)
{
    return c == '-' || c == '.' || c == '/';
};
bool isNumChar(const wchar_t c)
{
    return c >= '0' && c <= '9';
};
bool isDateStr(const std::wstring str)
{
    if (str.length() != 10)
        return false;
    if (!(isSpecialChar(str[4]) && isSpecialChar(str[7])))
        return false;

    std::wstring year = stepStr(str, 0, NUM);
    std::wstring month = stepStr(str, 5, NUM);
    std::wstring day = stepStr(str, 8, NUM);

    if (!(year.length() == 4 && month.length() == 2 && day.length() == 2))
        return false;

    int dayLimit[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (std::stoi(year) % 4 == 0 && (std::stoi(year) % 100 != 0 || std::stoi(year) % 400 == 0))
        dayLimit[2] = 29;

    if (year.compare(L"2000") < 0 || year.compare(L"2040") > 0 ||
        month.compare(L"01") < 0 || month.compare(L"12") > 0 ||
        day.compare(L"01") < 0 || std::stoi(day) > dayLimit[std::stoi(month) - 1])
        return false;

    return true;
}

std::wstring stepStr(std::wstring str, int start, StringType type)
{
    int i;
    switch (type)
    {
    case NORMAL:
        for (i = 0; i < str.length() - start; i++)
            if (!(isKorChar(str[start + i]) || isEngChar(str[start + i]) ||
                  isNumChar(str[start + i]) || isSpaceChar(str[start + i])))
                break;
        return str.substr(start, i);
    case PURE:
        for (i = 0; i < str.length() - start; i++)
            if (!(isKorChar(str[start + i]) || isEngChar(str[start + i]) || isNumChar(str[start + i])))
                break;
        return str.substr(start, i);
    case SPACE:
        for (i = 0; i < str.length() - start; i++)
            if (!isSpaceChar(str[start + i]))
                break;
        return str.substr(start, i);
    case BOOL:
        if (isBoolChar(str[start]))
            return str.substr(start, 1);
        else
            return str.substr(start, 0);
    case SPECIAL:
        for (i = 0; i < str.length() - start; i++)
            if (!isSpaceChar(str[start + i]))
                break;
        return str.substr(start, i);
    case DATE:
        if (isDateStr(str.substr(start, 10)))
            return str.substr(start, 10);
        else
            return str.substr(start, 0);
    case NUM:
        for (i = 0; i < str.length() - start; i++)
            if (!isNumChar(str[start + i]))
                break;
        return str.substr(start, i);
    default:
        throw "wrong string type";
    }
};

int dateCompare(std::wstring a, std::wstring b)
{
    if (!(isDateStr(a) && isDateStr(b)))
        throw "wrong date format";

    int yearA = std::stoi(a.substr(0, 4)),
        yearB = std::stoi(b.substr(0, 4));
    if (yearA != yearB)
        return (yearA > yearB) ? -1 : 1;

    int monthA = std::stoi(a.substr(5, 2)),
        monthB = std::stoi(b.substr(5, 2));
    if (monthA != monthB)
        return (monthA > monthB) ? -1 : 1;

    int dayA = std::stoi(a.substr(8, 2)),
        dayB = std::stoi(b.substr(8, 2));
    if (dayA != dayB)
        return (dayA > dayB) ? -1 : 1;

    return 0;
}