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

void printTask(Task);
Task findTask(Task *, const *);
void mkTask(char, char *, char *, char *);
bool isEqualTask(Task, Task);
bool isEnrolledTask(char *);
bool isOverlapped(Task, Task);
void taskDiagnosis(Task);