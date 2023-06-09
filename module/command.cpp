#include "command.h"
#include "userIO.h"
#include <vector>
#include <list>
#include "task.h"
#include <random>
#include <cstdlib>
#include <ctime>

std::vector<std::wstring>
parseParameter(std::wstring userInput, std::vector<StringType> syntax);
std::wstring getRandomString();

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
        L"[add] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [진리값] + [공백 문자열] + [진리값] + [개행 문자열]",
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
                                      SPACE,
                                      BOOL};
    std::vector<StringType> syntax2 = {NUM,
                                       SPACE,
                                       DURATION_UNIT};

    try
    {
        std::vector<std::wstring> parameters = parseParameter(userInput, syntax);

        task newTask;
        newTask.compatable = parameters[6];
        newTask.startDate = parameters[2];
        newTask.endDate = parameters[4];
        std::wstring recurringDurationUnit = L"D";
        std::wstring recurringGap = L"0";

        std::vector<task> newTasks;
        newTasks.push_back(newTask);

        if (dateCompare(newTask.startDate, newTask.endDate) == -1)
            throw L"인자1의 날짜는 인자2의 날짜보다 앞서거나 같아야 합니다.";

        std::list<task> registeredTasks = readTasks();
        for (const task &t : newTasks)
            if (hasOverlappingTask(registeredTasks, t))
                throw L"해당 기간에 이미 다른 일정이 등록되어 있습니다.";

        // 반복 일정일 경우
        if (parameters[8].compare(L"Y") == 0)
        {
            printSysMsg(L"반복 내용을 입력해 주세요.");
            std::vector<std::wstring> parameters2 = parseParameter(getUserInput(), syntax2);

            recurringDurationUnit = parameters2[2];
            recurringGap = parameters2[0];

            if (recurringGap.compare(L"0") == 0)
                throw L"반복 간격은 0보다 커야 합니다.";

            // 반복 일정 생성
            std::wstring sdate = addDate(newTask.startDate, recurringGap, recurringDurationUnit);
            std::wstring edate = addDate(newTask.endDate, recurringGap, recurringDurationUnit);
            while (stepStr(edate, 0, DATE).size() != 0)
            {
                task t;
                t.compatable = newTask.compatable;
                t.startDate = sdate;
                t.endDate = edate;

                sdate = addDate(sdate, recurringGap, recurringDurationUnit);
                edate = addDate(edate, recurringGap, recurringDurationUnit);

                newTasks.push_back(t);
            }
        }

        printSysMsg(L"일정 내용을 입력해 주세요");
        std::wstring contents = getUserInput();
        if (stepStr(contents, 0, NORMAL).length() != contents.length())
            throw L"한글과 알파벳, 숫자와 [0, /, .]만 지원됩니다. 일정 등록을 취소합니다.";

        // 반복 id
        std::wstring recurringId;
        if (parameters[8].compare(L"Y") == 0)
            do
            {
                recurringId = getRandomString();
            } while (isIdExists(registeredTasks, recurringId));
        else
            recurringId = L"0";

        for (task &t : newTasks)
        {
            t.contents = contents;
            t.recurringId = recurringId;
            t.recurringGap = recurringGap;
            t.recuuringDurationUnit = recurringDurationUnit;

            do
            {
                t.id = getRandomString();
            } while (isIdExists(registeredTasks, t.id) || recurringId.compare(t.id) == 0);

            registeredTasks.push_back(t);
        }

        writeTasks(registeredTasks);
        printSysMsg(L"일정이 등록되었습니다.");
        readTasks(); // 무결성 검사
    }
    catch (wchar_t const *err)
    {
        printSysMsg(err);
        return;
    }
}

void del(std::wstring userInput)
{
    std::vector<StringType> syntax1 = {PURE,
                                       SPACE,
                                       PURE};

    std::vector<StringType> syntax2 = {PURE,
                                       SPACE,
                                       DATE,
                                       SPACE,
                                       DATE};

    std::list<task> registeredTasks = readTasks();
    std::vector<std::wstring> parameters;
    std::list<task> targetTasks;
    try
    {
        parameters = parseParameter(userInput, syntax2);
        if (dateCompare(parameters[2], parameters[4]) == -1)
            throw L"인자1은 인자2보다 앞서거나 동일한 날짜여야 합니다.";
        targetTasks = startingTasksWithinPeriod(registeredTasks, parameters[2], parameters[4]);
        if (targetTasks.empty())
            throw L"해당하는 기간에 시작하는 일정이 없습니다.";
    }
    catch (wchar_t const *err)
    {
        if (!parameters.empty())
        {
            printSysMsg(err);
            return;
        }
    }

    try
    {
        if (parameters.empty())
        {
            parameters = parseParameter(userInput, syntax1);
            for (task t : registeredTasks)
                if (t.id.compare(parameters[2]) == 0 || t.recurringId.compare(parameters[2]) == 0)
                    targetTasks.push_back(t);

            if (targetTasks.empty())
                throw L"해당하는 id의 일정이 없습니다.";
        }
    }
    catch (wchar_t const *err)
    {
        printSysMsg(err);
        return;
    }

    for (task t : targetTasks)
        printTask(t);
    printSysMsg(L"위 일정을 삭제하시겠습니까? (Y/N)");

    std::wstring deleteConfirm = getUserInput();
    std::vector<StringType> deleteConfirmSyntax = {BOOL};
    try
    {
        if (parseParameter(deleteConfirm, deleteConfirmSyntax)[0].compare(L"Y") == 0)
        {
            printSysMsg(L"위 일정을 삭제합니다.");
            std::list<task>::iterator it = registeredTasks.begin();
            while (it != registeredTasks.end() && !targetTasks.empty())
            {
                if ((*targetTasks.begin()).id.compare((*it).id) == 0)
                {
                    targetTasks.erase(targetTasks.begin());
                    it = registeredTasks.erase(it);
                }
                else
                    it++;
            }

            writeTasks(registeredTasks);
        }
        else
        {
            printSysMsg(L"삭제를 취소합니다.");
        }

        readTasks();
    }
    catch (wchar_t const *err)
    {
        printSysMsg(L"문법에 맞지 않는 입력, 삭제를 취소합니다.");
    }
}

void search(std::wstring userInput)
{
    std::vector<StringType> syntax1 = {PURE};

    std::vector<StringType> syntax2 = {PURE,
                                       SPACE,
                                       DATE,
                                       SPACE,
                                       DATE};

    std::list<task> registeredTasks = readTasks();
    std::vector<std::wstring> parameters;
    std::list<task> targetTasks;

    try
    {
        parameters = parseParameter(userInput, syntax2);
        if (dateCompare(parameters[2], parameters[4]) == -1)
            throw L"검색 시작 날짜는 종료 날짜보다 늦을 수 없습니다.";
        targetTasks = overlappingTasks(registeredTasks, parameters[2], parameters[4]);
    }
    catch (wchar_t const *err)
    {
        if (!parameters.empty())
        {
            printSysMsg(err);
            return;
        }
    }

    try
    {
        if (parameters.empty())
        {
            parameters = parseParameter(userInput, syntax1);
            targetTasks = registeredTasks;
        }
    }
    catch (wchar_t const *err)
    {
        printSysMsg(err);
        return;
    }

    for (task t : targetTasks)
        printTask(t);
}

bool quit(std::wstring userInput)
{
    std::vector<StringType> syntax = {PURE};

    try
    {
        parseParameter(userInput, syntax);
    }
    catch (wchar_t const *err)
    {
        printSysMsg(err);
        return false;
    }

    printSysMsg(L"안녕히 가세요!");
    return true;
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

std::wstring getRandomString()
{
    std::wstring result;
    do
    {
        std::srand(std::time(nullptr));
        result.clear();
        for (int i = 0; i < 2; ++i)
        {
            int r = std::rand() % 3;
            switch (r)
            {
            case 0:
                result += static_cast<wchar_t>(std::rand() % (0xD7A3 - 0xAC00) + L'가');
                break;

            case 1:
                if (std::rand() % 2 == 0)
                {
                    result += static_cast<wchar_t>(std::rand() % 26 + 'a');
                }
                else
                {
                    result += static_cast<wchar_t>(std::rand() % 26 + 'A');
                }
                break;
            case 2:
                result += static_cast<wchar_t>(std::rand() % 10 + '0');
                break;
            }
        }
    } while (result.empty());
    return result;
}
