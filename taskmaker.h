#ifndef TASKMAKER_CLASS_H
#define TASKMAKER_CLASS_H

#include <iostream>
#include <string>
#include <limits>

// Class for making different tasks to the project, like taskName: Roofing, description: Lay roof on house, taskEstTime: 2 days, responsible: Rooflayer.
class Task
{
public:
    std::string taskName;
    std::string description;
    int taskEstTime;
    std::string responsible;

    void inputTaskDetails();
    void printTaskInfo() const;
    int getTaskEstTime() const;
    std::string getTaskName() const;
    void editTaskName();
    void editTaskDescription();
    void editTaskEstTime();
    void editTaskResponsible();

private:
    std::string validateTaskInfo(const std::string &prompt);
    int getValidInt(const std::string &prompt);
};

#endif // TASKMAKER_CLASS_H
