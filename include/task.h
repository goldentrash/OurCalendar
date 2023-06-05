#include <string>
#include <list>

struct task
{
    std::wstring id;
    std::wstring compatable;
    std::wstring startDate;
    std::wstring endDate;
    std::wstring contents;
    std::wstring recurringId;
    std::wstring recurringGap;
    std::wstring recuuringDurationUnit;
};

bool isIdExists(std::list<task> &, const std::wstring &);
std::list<task> readTasks();
void writeTasks(std::list<task>);
std::wstring toString(task);
void printTask(task);
bool hasOverlappingTask(std::list<task>, task);
std::list<task> overlappingTasks(std::list<task>, std::wstring, std::wstring);
std::list<task> startingTasksWithinPeriod(std::list<task>, std::wstring, std::wstring);