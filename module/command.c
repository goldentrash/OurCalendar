#include <command.h>
#include <userio.h>
#include <fileio.h>
#include <constants.h>
#include <task.h>
#include <string.h>

const int SNT_LIMIT = 10;

// 사용자 입력에서 인자를 파싱하고, 그럴 수 없으면 raise exception
// 예시)
// parseParameters("delete abc123\r\n", [PureStr, SpaceStr, PureStr, LnBrkStr], parameters);
// parameters[0]에는 첫 번째 인자가 저장된다.
int parseParameters(const char *usrIpt, const Str *cmdSyntax, const int syntaxLen, char parameters[SNT_LIMIT][INP_LIMIT])
{
    int now = 0;
    for (int i = 0; i < syntaxLen; i++)
    {
        int nxt = stepStr(usrIpt, now, cmdSyntax[i], parameters[i]);

        if (nxt == 0)
            return -1;

        now += nxt;
    }

    if (strlen(usrIpt) > now)
        return -1;

    return 1;
};

// 문자열을 받아서 명령어 종류 판가름
Cmd cmdType(const char *str)
{
    if (strType(str) == NotStr)
        return Help;

    char command[INP_LIMIT];
    stepStr(str, 0, PureStr, command);

    if (!strcmp(command, "add"))
        return Add;
    if (!strcmp(command, "delete"))
        return Del;
    if (!strcmp(command, "search"))
        return Search;
    if (!strcmp(command, "quit"))
        return Quit;

    return Help;
};

// help 명령어 실행
void help(const char *str)
{
    if (strType(str) == NotStr)
    {
        printSysMsg("한글과 알파벳, 숫자와 [-, /, .] 만 지원됩니다.");
        return;
    }

    char *syntaxs[7] = {
        "[help] + [공백 문자열] + [한 줄 문자열]",
        "[add] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [진리값] + [개행 문자열]",
        "[search] + [개행 문자열]",
        "[search] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [개행 문자열]",
        "[delete] + [공백 문자열] + [순수 문자열] + [개행 문자열]",
        "[delete] + [공백 문자열] + [날짜 문자열] + [공백 문자열] + [날짜 문자열] + [개행 문자열]",
        "[quit] + [개행 문자열]"};
    for (int i = 0; i < 7; i++)
        printSysMsg(syntaxs[i]);
};

// add 명령어 실행
void add(const char *str)
{
    const Str syntax[8] = {PureStr, SpaceStr, DateStr, SpaceStr, DateStr, SpaceStr, BooleanStr, LnBrkStr};
    char parameters[SNT_LIMIT][INP_LIMIT];

    if (parseParameters(str, syntax, 8, parameters) == -1)
    {
        printSysMsg("문법에 맞지 않는 입력입니다.");
        return;
    }

    char *stDate = parameters[2];
    char *enDate = parameters[4];
    char *comp = parameters[6];
    if (dateCmpr(stDate, enDate) == -1)
    {
        printSysMsg("유효하지 않은 기간입니다.");
        return;
    }

    if (strcmp(comp, "N") == 0 && findOverlappedTask(stDate, enDate).count != 0)
    {
        printSysMsg("해당 기간과 겹치는 일정이 있습니다.");
        return;
    }

    char contents[INP_LIMIT];
    getUsrIpt(contents);
    if (strType(contents) == NotStr)
    {
        printSysMsg("한글과 알파벳, 숫자와 [-, /, .] 만 지원됩니다.");
        return;
    }

    enrollTask(mkTask(comp[0], stDate, enDate, contents));
    printSysMsg("일정이 추가되었습니다.");
};

// del 명령어 실행
void del(const char *str)
{
    const Str syntax1[4] = {PureStr, SpaceStr, PureStr, LnBrkStr};
    const Str syntax2[6] = {PureStr, SpaceStr, DateStr, SpaceStr, DateStr, LnBrkStr};

    char parameters[SNT_LIMIT][INP_LIMIT];

    TaskList targets;
    Task targetTask;
    if (parseParameters(str, syntax1, 4, parameters) == 1)
    {
        char *id = parameters[2];
        if (isEnrolledTask(id) == -1)
        {
            printSysMsg("해당하는 id의 일정이 없습니다.");
            return;
        }

        targets.count = 1;
        targets.tasks[0] = findTask(id);
    }

    if (parseParameters(str, syntax2, 6, parameters) == 1)
    {
        char *stDate = parameters[2];
        char *enDate = parameters[4];
        if (dateCmpr(stDate, enDate) == -1)
        {
            printSysMsg("유효하지 않은 기간입니다.");
            return;
        }

        if (findTasks(stDate, enDate).count == 0)
        {
            printSysMsg("해당 기간에 등록된 일정이 없습니다.");
            return;
        }

        targets = findTasks(stDate, enDate);
    }

    printTasks(targets);
    printSysMsg("위 일정을 삭제하시겠습니까?");

    char *uip;
    char parameters2[SNT_LIMIT][INP_LIMIT];
    const Str syntax3[2] = {BooleanStr, LnBrkStr};
    getUsrIpt(uip);
    if (strType(uip) == NotStr ||
        parseParameters(uip, syntax3, 2, parameters2) == -1 ||
        strcmp(parameters2[0], "N") == 0)
    {
        printSysMsg("삭제를 취소합니다.");
        return;
    }

    printSysMsg("위 일정을 삭제합니다.");
    for (int i = 0; i < targets.count; i++)
        deleteTask(targets.tasks[i].id);
};

// search 명령어 실행
void search(const char *str)
{
    const Str syntax1[2] = {PureStr, LnBrkStr};
    const Str syntax2[6] = {PureStr, SpaceStr, DateStr, SpaceStr, DateStr, LnBrkStr};

    char parameters[SNT_LIMIT][INP_LIMIT];

    if (parseParameters(str, syntax1, 2, parameters) == 1)
    {
        printTasks(readFile());
    }

    if (parseParameters(str, syntax2, 6, parameters) == 1)
    {
        char *stDate = parameters[2];
        char *enDate = parameters[4];

        if (dateCmpr(stDate, enDate) == -1)
        {
            printSysMsg("유효하지 않은 기간입니다.");
            return;
        }

        printTasks(findOverlappedTask(stDate, enDate));
    };

    printSysMsg("문법에 맞지 않는 입력입니다.");
}
