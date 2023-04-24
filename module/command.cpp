#include <command.h>
#include <userIO.h>
#include <vector>
#include <list>
#include <task.h>

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
                                      BOOL};

    try
    {
        std::vector<std::wstring> parameters = parseParameter(userInput, syntax);

        task newTask;
        newTask.compatable = parameters[6];
        newTask.startDate = parameters[2];
        newTask.endDate = parameters[4];

        if (dateCompare(newTask.startDate,  newTask.endDate) == -1)
            throw L"시작 날짜가 종료 날짜보다 늦습니다.";

        std::list<task> registeredTasks = readTasks();
        if (hasOverlappingTask(registeredTasks, newTask))
            throw L"겹치는 일정이 있습니다.";

        printSysMsg(L"일정 내용을 입력해 주세요");
        newTask.contents = getUserInput();

        if (stepStr(newTask.contents, 0, NORMAL).length() != newTask.contents.length())
            throw L"한글과 알파벳, 숫자와 [0, /, .]만 지원됩니다. 일정 등록을 취소합니다.";

        if (registeredTasks.empty())
            newTask.id = L"0";
        else
            newTask.id = std::to_wstring(stoi(registeredTasks.back().id) + 1);

        registeredTasks.push_back(newTask);
        writeTasks(registeredTasks);
        printSysMsg(L"일정 " + newTask.id + L"가 등록되었습니다.");

        readTasks(); // 무결성 검사
    }
    catch (wchar_t const *err)
    {
        printSysMsg(err);
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
            throw L"문법에 맞지 않은 입력입니다.";

        parameters.push_back(parameter);
        cursor += parameter.length();
    }

    cursor += stepStr(userInput, cursor, SPACE).length();
    if (cursor != userInput.length())
        throw L"문법에 맞지 않은 입력입니다.";

    return parameters;
}
