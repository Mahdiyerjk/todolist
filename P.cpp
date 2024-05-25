#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task
{
public:
    string description;
    bool completed;

    Task(const std::string &desc) : description(desc), completed(false) {}
};

class ToDoList
{
private:
    vector<Task> taskList;

public:
    void addTask(const std::string &desc)
    {
        Task newTask(desc);
        taskList.push_back(newTask);
        cout << "Task added successfully." << endl;
    }

    void displayTasks()
    {
        for (int i = 0; i < taskList.size(); ++i)
        {
            cout << i + 1 << ". " << (taskList[i].completed ? "[X] " : "[ ] ") << taskList[i].description <<endl;
        }
    }

    void markAsComplete(int index)
    {
        if (index >= 1 && index <= taskList.size())
        {
            taskList[index - 1].completed = true;
            cout << "Task marked as complete." <<endl;
        }
        else
        {
            cout << "Invalid task index." << endl;
        }
    }

    void editTask(int index, const std::string &newDesc)
    {
        if (index >= 1 && index <= taskList.size())
        {
            taskList[index - 1].description = newDesc;
            cout << "Task updated successfully." << endl;
        }
        else
        {
            cout << "Invalid task index." <<endl;
        }
    }

    void removeTask(int index)
    {
        if (index >= 1 && index <= taskList.size())
        {
            taskList.erase(taskList.begin() + (index - 1));
            cout << "Task removed successfully." <<endl;
        }
        else
        {
            cout << "Invalid task index." <<endl;
        }
    }
};

int main()
{
    ToDoList todoList;
    
    int choice;
    do
    {
    	cout <<"............................"<< endl;
        cout << "To Do List" << endl;
        cout <<"............................"<< endl;
        cout << "1. Add New Task" << endl;
        cout << "2. Display All Tasks" << endl;
        cout << "3. Mark As Complete" << endl;
        cout << "4. Edit Task" << endl;
        cout << "5. Remove Task" << endl;
        cout << "0. Exit" << endl;
        cout << std::endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string newTaskDesc;
                cout << "Enter the description of the new task: ";
                cin.ignore();
                getline(std::cin, newTaskDesc);
                todoList.addTask(newTaskDesc);
                break;
            }
            case 2:
            {
                todoList.displayTasks();
                break;
            }
            case 3:
            {
                int index;
                cout << "Enter the index of the task to mark as complete: ";
                cin >> index;
                todoList.markAsComplete(index);
                break;
            }
            case 4:
            {
                int index;
                string newDesc;
                cout << "Enter the index of the task to edit: ";
                cin >> index;
                cout << "Enter the new description for the task: ";
                cin.ignore();
                getline(std::cin, newDesc);
                todoList.editTask(index, newDesc);
                break;
            }
            case 5:
            {
                int index;
                cout << "Enter the index of the task to remove: ";
                cin >> index;
                todoList.removeTask(index);
                break;
            }
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}