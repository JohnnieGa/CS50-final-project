#include <iostream>
#include <string>
#include <limits>

#include "project_functions.h"
#include "task_functions.h"
#include "projectmaker.h"
#include "taskmaker.h"

int getUserChoice();
bool projectMenu(Project &projectRef);
std::string enterProject();

int main()
{
    while (true)
    {
        int choice = getUserChoice();
        std::string projectName;
        Project *projectPtr;

        switch (choice)
        {
        case 1:
            createNewProject();
            break;
        case 2:
            findLargestProject();
            break;
        case 3:
            while (true)
            {
                projectName = enterProject();
                projectPtr = findProject(projectName);
                if (!projectPtr)
                {
                    continue;
                }
                else
                {
                    //Makes the raw pointer returned from findProject function to a reference instead
                    Project &projectRef = *projectPtr;
                    if (!projectMenu(projectRef))
                    {
                        break;
                    }
                }
            }
            break; // This ensures projectmenu option 4 makes it go back to main menu
        case 4:
            std::cout << "Exiting Program.\n";
            exit(0);
        default:
            std::cout << "Please enter a valid number.\n";
        }
    }

    return 0;
}

int getUserChoice()
{
    int choice;
    std::cout << "\nPress 1 to create a new project. Press 2 to list all active projects. Press 3 to enter the project menu. Press 4 to quit" << '\n';
    std::cin >> choice;

    if (std::cin.fail())
    {
        clearBufferFail();
        return -1;
    }

    return choice;
}

std::string enterProject()
{
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string input;

    listAllProjects();
    std::cout << "\nPlease enter the name of the project you want to enter: ";
    std::getline(std::cin, input);

    return input;
}

bool projectMenu(Project &projectRef)
{
    while (true)
    {
        int choice;
        std::cout << "\nPress 1 to add a task to the project. Press 2 to see the project information. Press 3 for the taskmanager. Press 4 to go back to the main menu\n";
        std::cin >> choice;

        if (std::cin.fail())
        {
            clearBufferFail();
            continue;
        }

        switch (choice)
        {
        case 1:
            if (!projectRef.createNewTask())
            {
                std::cout << "Something went wrong, please try again" << '\n';
            }
            break;
        case 2:
            projectRef.printProjectInfo();
            break;
        case 3:
            while (true)
                if (!taskMenu(projectRef))
                {
                    break;
                }
            break;
        case 4:
            return false;
        default:
            std::cout << "Please enter a valid number.\n";
        }
    }
    return true;
}
