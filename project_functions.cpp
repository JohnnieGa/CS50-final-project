#include "project_functions.h"

// Vector that stores all the projects made by the Project class
std::vector<std::unique_ptr<Project>> projects;

// Function that creates a new project from the Project class and puts it in the vector projects
void createNewProject()
{
    auto newProject = std::make_unique<Project>();
    newProject->inputProjectInfo();
    std::string projectName = newProject->getProjectName();
    projects.push_back(std::move(newProject));
    std::cout << "\nProject " << projectName << " created!\n";
}

// Function that lists up all the projects in order by when it was made
void listAllProjects()
{
    if (!checkProjectList())
    {
        return;
    }

    std::cout << "\nHere is a list of the existing projects: \n";

    for (const auto &project : projects)
    {
        std::cout << "\n - " << project->getProjectName();
    }

    // Prints a new line when loop is finished to make it look better
    std::cout << '\n';
}

// Function that takes a project name as a parameter and looks for that name in the vector.
// Returns a pointer to the project if found, or nullptr if not found.
Project *findProject(const std::string &selectedProject)
{

    // If the checkprojectlist function returns false there are no projects made, returns nullptr
    if (!checkProjectList())
    {
        return nullptr;
    }

    for (auto &project : projects)
    {
        if (selectedProject == project->getProjectName())
        {
            return project.get();
        }
    }

    std::cout << "\nPlease enter a valid project name.\n";

    return nullptr;
}

// Finding the largest project made based on the amount of task days in it, and list all projects based on task days
void findLargestProject()
{
    if (!checkProjectList())
    {
        return;
    }

    std::vector<std::pair<int, std::string>> projectDays;

    // Get all the task hours from a project via getDaysOfTasks from the Project class, store it in projectdays vector along side with the project name for easy fetching later
    for (const auto &project : projects)
    {
        int daysPerProject = project->getTotalDaysOfTasks();
        std::string projectName = project->getProjectName();
        projectDays.push_back(std::make_pair(daysPerProject, projectName));
    }

    // Sort the pair vector in falling order based on the first element in the pair(int daysPerProject)
    std::sort(projectDays.begin(), projectDays.end(), [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b)
              {

        // Lambda function that compares b.first (one int) with a.first (second int from another pair). Returns true if b is smaller than a.
        return b.first < a.first; });

    // Print the projects from the pair vector, with the project with the most task hours first and decending
    for (size_t i = 0; i < projectDays.size(); ++i)
    {
        const auto &[days, project] = projectDays[i];
        std::cout << i + 1 << ". " << project << " - Total " << days << " Days" << '\n';
    }
}

// Check that there actually is projects made by checking size of vector projects
bool checkProjectList()
{
    if (projects.size() == 0)
    {
        std::cout << "There are no projects made. Please make a project before adding a task\n";
        return false;
    }
    else
    {
        return true;
    }
}
