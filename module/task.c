#include <task.h>
#include <fileio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

char *pureStr(); // 순수문자열 생성

int isIdEqualTask(Task, char *); // 일정과 id간 동일한 일정인지 확인 (id 기준)

// 일정 배열을 terminal에 출력
void printTasks(TaskList taskList)
{
    for (int i = 0; i < taskList.count; i++)
        printf("%s/t%c %s~%s\n%s\n", taskList.tasks[i].id, taskList.tasks[i].compatable, taskList.tasks[i].startDate, taskList.tasks[i].endDate, taskList.tasks[i].contents);
};

// 일정 생성 (id 자동 생성)
Task mkTask(char compatable, char *startDate, char *endDate, char *contents)
{
    Task task;
    task.compatable = compatable;
    task.startDate = startDate;
    task.endDate = endDate;
    task.contents = contents;
    task.id = pureStr(); // 길이 2의 순수문자열(한글, 알파벳, 숫자)
    return task;
};

// 두 일정 간 동일한 일정인지 확인 (id 기준)
int isEqualTask(Task a, Task b)
{
    if (strcmp(a.id, b.id) == 0)
        return 1;
    else
        return -1;
};

// 일정과 id간 동일한 일정인지 확인
int isIdEqualTask(Task a, char *id)
{
    if (strcmp(a.id, id) == 0)
        return 1;
    else
        return -1;
};

// 등록된 일정인지 확인 -> 삭제할 때 찾는 함수
int isEnrolledTask(char *id)
{
    TaskList taskList = readFile();
    Task *alltaskarray = taskList.tasks;
    for (int i = 0; i < taskList.count; i++)
    {
        if (isIdEqualTask(alltaskarray[i], id))
        {
            free(alltaskarray);
            return 1;
        }
    }
    free(alltaskarray);
    return -1;
}

// 일정이 겹치는지 확인
int isOverlapped(Task a, Task b)
{
    if ((strcmp(a.startDate, b.endDate) <= 0) && (strcmp(a.endDate, b.startDate) >= 0))
        return 1; // 겹치면 1 반환
    else
        return -1;
};

// 입력한 기간에 시작하는 모든 등록된 일정 반환
TaskList findTasks(char *startDate, char *endDate)
{
    TaskList taskList = readFile();
    int n = 0;
    Task *alltaskarray = taskList.tasks;
    for (int i = 0; i < taskList.count; i++)
    {
        if ((strcmp(startDate, alltaskarray[i].startDate) <= 0) &&
            (strcmp(alltaskarray[i].startDate, endDate) <= 0))
            n++;
    }

    if (n == 0)
    {
        free(alltaskarray);
        return (TaskList){.tasks = NULL, .count = 0};
    }

    Task *taskarray = (Task *)malloc(sizeof(Task) * n);

    int j = 0;
    for (int i = 0; i < taskList.count; i++)
    {
        if ((strcmp(startDate, alltaskarray[i].startDate) <= 0) &&
            (strcmp(alltaskarray[i].startDate, endDate) <= 0))
        {
            taskarray[j] = alltaskarray[i];
            j++;
        }
    }

    TaskList sttaskList = {.tasks = taskarray, .count = n};
    free(alltaskarray);
    return sttaskList;
}

// 입력한 기간과 겹치는 등록된 일정을 찾는 함수
TaskList findOverlappedTask(char *startDate, char *endDate)
{
    TaskList taskList = readFile();
    int n = 0;
    Task *alltaskarray = taskList.tasks;
    for (int i = 0; i < taskList.count; i++)
    {
        if (strcmp(startDate, alltaskarray[i].endDate) <= 0 && strcmp(endDate, alltaskarray[i].startDate) >= 0)
            n++;
    }

    if (n == 0)
    {
        free(alltaskarray);
        return (TaskList){.tasks = NULL, .count = 0};
    }

    Task *taskarray = (Task *)malloc(sizeof(Task) * n);

    int j = 0;
    for (int i = 0; i < taskList.count; i++)
    {
        if (strcmp(startDate, alltaskarray[i].endDate) <= 0 && strcmp(endDate, alltaskarray[i].startDate) >= 0)
        {
            taskarray[j] = alltaskarray[i];
            j++;
        }
    }

    TaskList overlappedtaskList = {.tasks = taskarray, .count = n};
    free(alltaskarray);
    return overlappedtaskList;
}

// 해당하는 id의 일정 반환
Task findTask(char *id)
{
    TaskList taskList = readFile();
    Task *alltaskarray = taskList.tasks;
    Task task = {0};
    for (int i = 0; i < taskList.count; i++)
    {
        if (isIdEqualTask(alltaskarray[i], id))
        {
            task = alltaskarray[i];
            return task;
        }
    }
    return task;
}

// 순수문자열을 생성하는 함수
char *pureStr()
{
    char *purestr = (char *)malloc(3); // 2글자 + NULL 문자를 위한 3바이트 할당
    srand(time(NULL));                 // 랜덤 시드 초기화
    for (int i = 0; i < 2; i++)
    {
        int type = rand() % 2; // 0 ~ 1 중 하나의 숫자를 랜덤하게 선택
        switch (type)
        {
        case 0: // 숫자 선택
            purestr[i] = rand() % 10 + '0';
            break;
        case 1: // 영어 알파벳 선택
            if (rand() % 2 == 0)
            {
                purestr[i] = rand() % 26 + 'a'; // 소문자 선택
            }
            else
            {
                purestr[i] = rand() % 26 + 'A'; // 대문자 선택
            }
            break;
           
        }
    }
    purestr[2] = '\0'; // 문자열 끝에 NULL 문자 추가
    return purestr;
}
