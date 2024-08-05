# Project Manager
#### Description:
For my final project in cs50x i made a project manager. The program is a terminal program written in c++. The program is built up so that the user first creates a project or more, and then fills a selected project with different tasks. The main point with projects is that they can be split up in different tasks that has to be completed to get the project done. When the user add tasks to the project they get to fill in information about task name, description, task estimated time and whos responsible for the task. As the task estimated time is filled in so is the project end date. If the starting date of a project is 2024-07-01 and that projects get added with a task that has a estimated time of 3 days the projects end date gets set 2024-07-01 + the three days of the task. If the user puts in more tasks with more various estimated times, the end date sets further and further in the future. A task can then get deleted or edited wich both affects the end date.


##### Main:
The main file contains a while loop inside the main function that gets the user to the main menu. Here the user gets the choice to create a project, list all made projects, enter a project or quit the program. If the user choose to create a new project it calls a function inside the file project_functions that creates a new project. It then creates an object from the Project class. The object is then collected in a vector of unique ptrs. Choice number two, list all the projects, uses a function inside the project_function. The output will then list all the made projects based on size.

The third option in main menu takes the user to the "project menu". The user gets to input the name of the project they want to enter. That input is then sent to another function inside project_functions that returns a pointer to the project. To see that the users input was valid the function that returns the Project ptr returns a nullptr if there is no project name that equals the input.

A reflection inside my main file is the structure. From my understanding the main function should make it easy to follow along the code and program by just looking at that function. My main file could look a little bloated, but i do think it achives some easy following and understandable code. The projectmenu is also in this file. I thought about making a separate file for all the menus in the program, but that would make the main function small and maybe make the program less understandable.

##### project_functions:
The file project_functions contains functions that handles the project. The create new project function, as mentioned earlier, creates a new project. Another function is the list all projects function that returns a list of all the created projects name. Unlike the list all projects function thats accessable through the main menu that sorts the list based on time, this list is not sorted. The function is used for when a user wants to enter a project and need to type in the project name.

The listing function from the main menu that outputs the projects based on time is in this file. In the function i created a paired vector to create a sort of key value list. First i go through the project vector and gather the estimated time for a project, paired with the project name and put it in the vector. To then sort that vector i used the function std::sort with a lambda function. This function compares the two ints next to each other in the vector and returns true if the first int is smaller then the other.

##### task_functions:
In the file task_functions i have the task related functions. When the user have created a project, entered the project menu and then the task menu, they can from here choose to see all the tasks in that project. This function lists up all the tasks inside the project based on size of the task. For this i used a different approach then the paired vector mentioned above. When the user first creates a project with the Project class, an empty vector is also created by the class. When the user then creates a task (inside project_functions) that task has it owns class that looks similar to the Project class. It then stores that task object inside that vector made by the Project class. When the object is inserted in to the vector it checks if the new tasks estimated time is larger then the ones already inside the vector and inserts it in the right spot.

Other functions here is to delete a task, wich does what it says. It deletes the task with the help of the Project class that has the object stored in a vector. The function to edit a task makes it possible to edit a task thats already made. The user gets to choose wich info in the task to edit, and then calls a function from the Task class to set the new information on the edited task. To get the particular task object i used a similar approach as to get a particular project. It calls a function inside the Project class that returns a pointer and uses that to call the tasks functions inside the Task class.

##### projectmaker:
This file contains the Project class. As mentioned above its a class that creates an object of a new project made by the user. When created, the user gets to input information for the project. To check that the input is valid there is a validate function. This checks that all inputs that expects a string is not empty, the input that expects an int is a valid int and the starting date is a real date. If these validating functions doesnt give the right return value, the user gets reprompted with an error message. To handle the starting date input i used the iomanip library and the sstream library. By using functions from these libraries i was able to check that the input starting date wasnt backwards in time, the date was formatted right and able to set an end date based on task estimated times. When trying to figure this out i found that c++20 uses an updated version of the chrono library. My project was written using c++17 so i couldnt use it, but in the future i would use this because it looks less complicated when handling dates and times.

##### taskmaker:
The taskmaker file is the Task class. Its similar to the Project class with a few differences. The user gets to input the information on the task when created and that information gets validated in the same way as the project information, but this information can be edited unlike the project information. It has a function for each of its information values that gets the new value when called upon. The input gets validated again using the in class function for validation and if everything checks out a new value is stored for the object.
