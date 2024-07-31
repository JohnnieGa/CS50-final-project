#include "task_functions.h"

bool taskMenu(Project &selectedProject)
{
    if (!checkTaskList(selectedProject))
    {
        return false;
    }

    while (true)
    {
        int choice;
        std::cout << "\nPress 1 to list all tasks for the project. Press 2 delete a task. Press 3 to edit a task. Press 4 to go back to the project menu\n";
        std::cin >> choice;

        if (std::cin.fail())
        {
            clearBufferFail();
            continue;
        }

        switch (choice)
        {
        case 1:
            findAllTaskDays(selectedProject);
            break;
        case 2:
            if (!deleteTask(selectedProject))
            {
                return false;
                break;
            }
            break;
        case 3:
            editTask(selectedProject);
            break;
        case 4:
            return false;
        default:
            std::cout << "Please enter a valid number.\n";
        }
    }
}

// A function that displays tasks ranked based on taskesttime. Not to mix with the one from project_functions that returns sums of all projects, this is for a single chosen project.
void findAllTaskDays(Project &selectedProject)
{
    int printedIndex = 1;

    for (auto &project : projects)
    {

        // allTasks contains the returned vector for all the tasks made in the selectedProject.
        if (selectedProject.getProjectName() == project->getProjectName())
        {
            const auto &allTasks = project->getAllTaskVector();
            for (auto &task : allTasks)
            {
                std::cout << printedIndex << ". " << task->getTaskName() << " - Total " << task->getTaskEstTime() << " Days" << '\n';
                printedIndex++;
            }
        }
    }
}

void listAllTasks(Project &selectedProject)
{
    const auto &allTasks = selectedProject.getAllTaskVector();

    std::cout << "\nHere is a list of the existing tasks related to the project:\n ";

    for (auto &task : allTasks)
    {
        std::cout << "\n - " << task->getTaskName();
    }

    std::cout << '\n';
}

bool deleteTask(Project &selectedProject)
{
    if (!checkTaskList(selectedProject))
    {
        return false;
    }
    std::string input;
    while (true)
    {
        listAllTasks(selectedProject);
        std::cout << "\nType in the name of a task to delete: " << '\n';
        std::getline(std::cin, input);

        auto taskPtr = selectedProject.findTask(input);

        if (!taskPtr)
        {
            std::cout << "Please enter a valid taskname" << '\n';
            continue;
        }
        else
        {
            Task &selectedTask = *taskPtr;
            selectedProject.deleteTask(selectedTask);
            return true;
            break;
        }
        break;
    }
    return true;
}

bool checkTaskList(Project &selectedProject)
{
    const auto &allTasks = selectedProject.getAllTaskVector();

    if (allTasks.size() == 0)
    {
        std::cout << "This project has no tasks. Please make a task before entering the taskmenu" << '\n';
        return false;
    }

    return true;
}

void editTask(Project &selectedProject)
{
    std::cin.ignore();
    while (true)
    {
        listAllTasks(selectedProject);
        std::string input;
        std::cout << "\nSelect the task you would like to edit: ";
        std::getline(std::cin, input);

        auto taskPtr = selectedProject.findTask(input);

        if (!taskPtr)
        {
            std::cout << "Please enter a valid task name" << '\n';
            continue;
        }
        else
        {
            Task &selectedTask = *taskPtr;

            std::cout << "\nHere is the tasks information:" << '\n';
            selectedTask.printTaskInfo();
            int taskInfoToEdit;

            std::cout << "\nPress 1 to edit Task Name, 2 for Task description, 3 for Task Estimated Time, 4 for Responsible Part and 5 for printing taskinfo." << '\n';
            std::cin >> taskInfoToEdit;
            std::string newInformation;
            std::cin.ignore();

            if (std::cin.fail())
            {
                clearBufferFail();
                continue;
            }

            switch (taskInfoToEdit)
            {
            case 1:
                selectedTask.editTaskName();
                break;
            case 2:
                selectedTask.editTaskDescription();
                break;
            case 3:
                selectedTask.editTaskEstTime();
                break;
            case 4:
                selectedTask.editTaskResponsible();
                break;
            case 5:
                selectedTask.printTaskInfo();
                break;
            default:
                std::cin.ignore();
                std::cout << "Please enter a valid number.\n";
                continue;
            }
        }
        break;
    }
}

void clearBufferFail()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a valid number.\n";
}