#ifndef PROJECTMAKER_CLASS_H
#define PROJECTMAKER_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "taskmaker.h"

// Class Project for making a new project
class Project
{
private:
    std::string projectName;                  // Name of the project
    std::string projectAddress;               // Address of the project
    std::string customerName;                 // Customer for the project
    std::tm startDate;                        // Start date of the project
    std::vector<std::unique_ptr<Task>> tasks; // All the task objects created for the project gathered in a vector

    std::tm getCurrentDate();
    std::tm setStartDate();
    bool isDateInThePast(const std::tm &inputDate, const std::tm &currentDate);
    void getProjectEndDate();
    std::string validateProjectInfo(const std::string &prompt);

public:
    void inputProjectInfo();
    bool createNewTask();
    void printProjectInfo();
    const std::string &getProjectName() const;
    int getTotalDaysOfTasks() const;
    std::vector<std::unique_ptr<Task>> &getAllTaskVector();
    Task *findTask(const std::string &selectedTask);
    void deleteTask(Task &taskToDelete);
};

#endif // PROJECTMAKER_CLASS_H
