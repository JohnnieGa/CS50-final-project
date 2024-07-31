#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <algorithm>


#include "projectmaker.h"

// Extern declaration of the vector projects
extern std::vector<std::unique_ptr<Project>> projects;

// Declarations for projectrelated functions
void createNewProject();
void listAllProjects();
Project *findProject(const std::string &selectedProject);
void findLargestProject();
bool checkProjectList();

#endif