#include "projectmaker.h"

// Get and insert the information from the user to the project as project name, address, customer name, and starting date of the project
void Project::inputProjectInfo()
{
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    projectName = validateProjectInfo("\nEnter Project Name: ");
    projectAddress = validateProjectInfo("Enter Project Address: ");
    customerName = validateProjectInfo("Enter Customer Name: ");

    startDate = setStartDate();
}

std::string Project::validateProjectInfo(const std::string &prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Please enter a valid input for the project info.\n";
            continue;
        }
        else
        {
            return input;
        }
    }
}

// Add tasks to the project with a name, description of the task, estimated time and who is responsible for the task. Uses Task class similar to Project class.
// Returns true if everything goes as it should
bool Project::createNewTask()
{

    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    auto newTask = std::make_unique<Task>();
    newTask->inputTaskDetails();

    // Sort the vector with tasks right away by seeing if the new task has a larger taskEstTime than the one in front of the vector.
    // If the vector is empty just push_back the new task
    if (tasks.size() == 0)
    {
        tasks.push_back(std::move(newTask));
        return true;
    }

    if (newTask->getTaskEstTime() <= tasks[0]->getTaskEstTime())
    {
        tasks.push_back(std::move(newTask));
        return true;
    }
    else
    {
        tasks.insert(tasks.begin(), std::move(newTask));
        return true;
    }

    return false;
}

void Project::printProjectInfo()
{
    std::cout << "\nProject Name: " << projectName << '\n';
    std::cout << "Address: " << projectAddress << '\n';
    std::cout << "Customer: " << customerName << '\n';
    std::cout << "Number of tasks related to the project: " << tasks.size() << '\n';
    std::cout << "Starting Date: " << std::put_time(&startDate, "%Y-%m-%d") << std::endl;
    getProjectEndDate();
}

const std::string &Project::getProjectName() const
{
    return projectName;
}

// Returns the sum of all the taskesttime combined for the projects
int Project::getTotalDaysOfTasks() const
{
    std::vector<int> daysOfTasks;
    for (const auto &task : tasks)
    {
        int days = task->getTaskEstTime();
        daysOfTasks.push_back(days);
    }

    int sum = std::accumulate(daysOfTasks.begin(), daysOfTasks.end(), 0);
    return sum;
}

// Returns the vector that holds all the tasks related to the project
std::vector<std::unique_ptr<Task>> &Project::getAllTaskVector()
{
    return tasks;
}

// Function to find a specific task and return that task in a pointer to the user
Task *Project::findTask(const std::string &selectedTask)
{
    if (tasks.size() == 0)
    {
        std::cout << "No tasks available for this project, please make a new task before searching" << '\n';
        return nullptr;
    }

    for (auto &task : tasks)
    {
        if (selectedTask == task->getTaskName())
        {
            return task.get();
        }
    }

    return nullptr;
}

void Project::deleteTask(Task &taskToDelete)
{
    auto newEnd = std::remove_if(tasks.begin(), tasks.end(),
                                 [&taskToDelete](const std::unique_ptr<Task> &task)
                                 {
                                     return task.get() == &taskToDelete;
                                 });

    tasks.erase(newEnd, tasks.end());

    std::cout << "Task deleted!" << '\n';
}

// Takes input to get the starting date from the user, makes it to a tm object, then checks that the input date is not backwards in time and of right dateformat.
std::tm Project::setStartDate()
{
    while (true)
    {
        std::string date;
        std::cout << "Enter Start Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);

        std::tm tm = {};
        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail())
        {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
            continue;
        }

        std::tm todaysDate = getCurrentDate();

        if (isDateInThePast(tm, todaysDate))
        {
            std::cout << "\nPlease enter a date that is in the future, not earlier than today.\n";
            continue;
        }

        return tm;
    }
}

std::tm Project::getCurrentDate()
{
    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    return *tm;
}

bool Project::isDateInThePast(const std::tm &inputDate, const std::tm &currentDate)
{
    return std::mktime(const_cast<std::tm *>(&inputDate)) < std::mktime(const_cast<std::tm *>(&currentDate));
}

// Figures out a end date to the project by taking the sum of all taskdays and adds it to the startdate
void Project::getProjectEndDate()
{
    std::tm newDate = startDate;

    std::time_t time = std::mktime(const_cast<std::tm *>(&newDate));

    time += getTotalDaysOfTasks() * 86400;

    std::tm *result = std::localtime(&time);

    std::cout << "End Date: " << std::put_time(result, "%Y-%m-%d") << '\n';
}