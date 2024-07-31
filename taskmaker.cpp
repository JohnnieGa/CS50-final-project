#include "taskmaker.h"

void Task::inputTaskDetails()
{
    taskName = validateTaskInfo("\nEnter The Task Name: ");
    description = validateTaskInfo("Enter Task Description (ex. tiling the kitchen): ");
    taskEstTime = getValidInt("Enter The Estimated Time For The Task In Days: ");
    responsible = validateTaskInfo("Enter The Responsible Part For Doing The Task: ");

    std::cout << "\nTask " << taskName << " created!" << '\n';
}

std::string Task::validateTaskInfo(const std::string &prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Please enter a valid input for the task info.";
            continue;
        }
        else
        {
            return input;
        }
    }
}

int Task::getValidInt(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nPlease enter a valid number greater than 0.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void Task::printTaskInfo() const
{
    std::cout << "Taskname: " << taskName << '\n';
    std::cout << "Description: " << description << '\n';
    std::cout << "Estimated Time: " << taskEstTime << '\n';
    std::cout << "Responsible: " << responsible << '\n';
}

int Task::getTaskEstTime() const
{
    return taskEstTime;
}

std::string Task::getTaskName() const
{
    return taskName;
}

void Task::editTaskName()
{
    taskName = validateTaskInfo("\nWhat would you like the new taskname to be? ");
}

void Task::editTaskDescription()
{
    description = validateTaskInfo("\nWhat would you like the new task description to be? ");
}

void Task::editTaskEstTime()
{
    taskEstTime = getValidInt("\nWhat would you like the new task estimated time to be? ");
}

void Task::editTaskResponsible()
{
    responsible = validateTaskInfo("\nWho would you like the responsible for the task to be? ");
}
