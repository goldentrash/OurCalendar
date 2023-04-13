#include <stdbool.h>
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
    Task* tasks;
    int count;
} TaskList;

Task mkTask(char, char *, char *, char *);
int isEqualTask(Task, Task);
int isEnrolledTask(char *);
int isOverlapped(Task, Task);
int taskDiagnosis(Task);
void printTasks(TaskList);
TaskList findTasks(char *, char *);
TaskList findOverlappedTask(char *, char *);
