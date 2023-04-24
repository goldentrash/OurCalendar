#include <command.h>
#include <userIO.h>
#include <vector>

std::vector<std::wstring>
parseParameter(std::wstring userInput, std::vector<StringType> syntax);

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

void help(std::wstring userInput)
{
    if (stepStr(userInput, 0, NORMAL).length() != userInput.length())
    {
        printSysMsg(L"한글과 알파벳, 숫자와 [-, /, .] 만 지원됩니다.");
        return;
    }

    std::wstring syntaxes[] = {
        L"[help] + [공백 문자열] + [한 줄 문자열]",
        L"[add] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [진리값] + [개행 문자열]",
        L"[search] + [개행 문자열]",
        L"[search] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [개행 문자열]",
        L"[delete] + [공백 문자열] + [순수 문자열] + [개행 문자열]",
        L"[delete] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [개행 문자열]",
        L"[quit] + [개행 문자열]"};
    for (std::wstring syntax : syntaxes)
        printSysMsg(syntax);
}

void add(std::wstring userInput)
{
    std::vector<StringType> syntax = {PURE,
                                      SPACE,
                                      DATE,
                                      SPACE,
                                      DATE,
                                      SPACE,
                                      BOOL,
                                      SPACE};

    try
    {
        std::vector<std::wstring> parameters = parseParameter(userInput, syntax);
        if (dateCompare(parameters[2], parameters[4]) == -1)
            throw "start date > end date";
    }
    catch (std::string err)
    {
        if (err.compare("wrong at syntax") == 0)
            printSysMsg(L"문법에 맞지 않는 입력입니다.");

        if (err.compare("start date > end date") == 0)
            printSysMsg(L"시작 날짜가 종료 날짜보다 느립니다.");

        return;
    }
}

std::vector<std::wstring> parseParameter(std::wstring userInput, std::vector<StringType> syntax)
{
    int cursor = 0;
    std::vector<std::wstring> parameters;
    for (StringType parameterType : syntax)
    {
        std::wstring parameter = stepStr(userInput, cursor, parameterType);

        if (parameter.length() == 0)
            throw "wrong at syntax";

        parameters.push_back(parameter);
        cursor += parameter.length();
    }

    if (cursor != userInput.length())
        throw "wrong at syntax";

    return parameters;
}
