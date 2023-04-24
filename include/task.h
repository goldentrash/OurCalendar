#include <string>
#include <list>

struct task
{
    std::wstring id;
    std::wstring compatable;
    std::wstring startDate;
    std::wstring endDate;
    std::wstring contents;
};

std::list<task> readTasks();
void writeTasks(std::list<task>);
std::wstring toString(task);
void printTask(task);
bool hasOverlappingTask(std::list<task>, task);
std::list<task> startingTasksWithinPeriod(std::list<task>, std::wstring, std::wstring);