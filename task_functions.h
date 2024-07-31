#ifndef TASK_FUNCTIONS_H
#define TASK_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

#include "project_functions.h"
#include "projectmaker.h"
#include "taskmaker.h"

void findAllTaskDays(Project &selectedProject);
bool taskMenu(Project &selectedProject);
void listAllTasks(Project &selectedProject);
bool deleteTask(Project &selectedProject);
bool checkTaskList(Project &selectedProject);
void editTask(Project &selectedProject);
void clearBufferFail();

#endif