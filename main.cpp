#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(string desc, bool status = false) {
        description = desc;
        completed = status;
    }
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask() {
        string desc;
        cout << "Enter task description: ";
        cin.ignore();
        getline(cin, desc);

        tasks.push_back(Task(desc));
        cout << "Task added successfully!\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "\n----- Task List -----\n";
        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].description;
            if (tasks[i].completed)
                cout << " [Completed]";
            else
                cout << " [Pending]";
            cout << endl;
        }
    }

    void markCompleted() {
        int choice;
        viewTasks();
        if (tasks.empty()) return;

        cout << "Enter task number to mark as completed: ";
        cin >> choice;

        if (choice > 0 && choice <= tasks.size()) {
            tasks[choice - 1].completed = true;
            cout << "Task marked as completed!\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void saveToFile() {
        ofstream file("tasks.txt");

        for (int i = 0; i < tasks.size(); i++) {
            file << tasks[i].description << "|" << tasks[i].completed << endl;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("tasks.txt");
        string line;

        while (getline(file, line)) {
            int pos = line.find("|");
            string desc = line.substr(0, pos);
            bool status = stoi(line.substr(pos + 1));
            tasks.push_back(Task(desc, status));
        }

        file.close();
    }
};

int main() {
    ToDoList todo;
    int choice;

    todo.loadFromFile();

    do {
        cout << "\n===== TO-DO LIST MENU =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            todo.addTask();
            break;
        case 2:
            todo.viewTasks();
            break;
        case 3:
            todo.markCompleted();
            break;
        case 4:
            todo.saveToFile();
            cout << "Tasks saved. Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}