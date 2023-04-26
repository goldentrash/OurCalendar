#include <task.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <userIO.h>

const std::string DATA_PATH = "./data.csv";

bool isIdExists(std::list<task> &tasks, const std::wstring &id)
{
    for (task &t : tasks)
    {
        if (t.id.compare(id) == 0)
        {
            return true;
        }
    }
    return false;
}

std::list<task> readTasks()
{
    std::wifstream fin;
    fin.open(DATA_PATH);

    if (!fin.is_open())
    {
        std::wofstream fout;
        fout.open(DATA_PATH);
        fout << std::endl;
        fout.close();
        fin.open(DATA_PATH);
    }

    std::list<task> tasks;
    while (!fin.eof())
    {
        std::wstring line;
        getline(fin, line);
        if (line.length() == 0)
            break;

        task t;
        std::wistringstream sin(line);
        getline(sin, t.id, L',');
        getline(sin, t.compatable, L',');
        getline(sin, t.startDate, L',');
        getline(sin, t.endDate, L',');
        getline(sin, t.contents, L',');

        if (isIdExists(tasks, t.id))
        {
            printSysMsg(L"데이터 파일이 손상되었습니다.");
            exit(EXIT_FAILURE);
        }

        tasks.push_back(t);
    }
    fin.close();
    return tasks;
}

void writeTasks(std::list<task> tasks)
{
    std::wofstream fout;
    fout.open(DATA_PATH, std::fstream::out | std::ios::trunc);
    if (!fout.is_open())
        return;
    for (task t : tasks)
    {
        std::wstring s = toString(t);
        fout << s << std::endl;
    }
    fout.close();
}

std::wstring toString(task t)
{
    return t.id + L"," + t.compatable + L"," +
           t.startDate + L"," + t.endDate + L"," + t.contents;
}

void printTask(task t)
{
    printSysMsg(t.id + L"\t" + t.compatable + L" " + t.startDate + L" ~ " + t.endDate);
    printSysMsg(t.contents);
}

bool hasOverlappingTask(std::list<task> registeredTasks, task newTask)
{
    return std::find_if(registeredTasks.begin(), registeredTasks.end(),
                        [newTask](task t)
                        {
                            if (newTask.compatable.compare(L"N") == 0 || t.compatable.compare(L"N") == 0)
                                return !(dateCompare(newTask.startDate, t.endDate) == -1 ||
                                         dateCompare(newTask.endDate, t.startDate) == 1);
                            else
                                return false;
                        }) != registeredTasks.end();
}

std::list<task> overlappingTasks(std::list<task> registeredTasks, std::wstring startDate, std::wstring endDate)
{
    std::list<task> tasks;
    for (task t : registeredTasks)
        if (!(dateCompare(startDate, t.endDate) == -1 ||
              dateCompare(endDate, t.startDate) == 1))
            tasks.push_back(t);

    return tasks;
}

std::list<task> startingTasksWithinPeriod(std::list<task> registeredTasks, std::wstring startDate, std::wstring endDate)
{
    std::list<task> tasks;
    for (task t : registeredTasks)
        if (!(dateCompare(startDate, t.startDate) == -1 || dateCompare(t.startDate, endDate) == -1))
            tasks.push_back(t);

    return tasks;
}
