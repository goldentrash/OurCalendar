#include <task.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <userIO.h>

const std::string DATA_PATH = "./data.csv";

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

bool hasOverlappingTask(std::list<task> registeredTasks, task newTask)
{
    return std::find_if(registeredTasks.begin(), registeredTasks.end(),
                        [newTask](task t)
                        {
                            if (newTask.compatable.compare(L"Y") == 0 || t.compatable.compare(L"Y") == 0)
                                return !(dateCompare(newTask.startDate, t.endDate) == -1 ||
                                         dateCompare(newTask.endDate, t.startDate) == 1);
                            else
                                return false;
                        }) != registeredTasks.end();
}