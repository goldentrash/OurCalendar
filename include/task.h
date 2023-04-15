#include <constants.h>

typedef struct
{
    char *id;
    char compatable;
    char *startDate;
    char *endDate;
    char *contents;
} Task;

typedef struct
{
    Task *tasks;
    int count;
} TaskList;

Task mkTask(char, char *, char *, char *);
int isEqualTask(Task, Task);
int isEnrolledTask(char *);
int isOverlapped(Task, Task);
void printTasks(TaskList);
Task findTask(char *); // 입력한 id의 해당 일정 반환
TaskList findTasks(char *, char *);
TaskList findOverlappedTask(char *, char *);
