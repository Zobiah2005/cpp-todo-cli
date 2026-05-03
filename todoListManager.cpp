#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

struct task {   //task represents a single to-do item 
    char task_about[100]; //task_about holds task description
    struct task* next;     // pointer to next task in the list
};

struct category {  //category list (holds a group i.e. "Work", "Home" etc.)
    char category_name[100];    //holds the name of the category 
    struct task* task_list;     // Points to the first task in the category 
    struct category* next;      // points to the next category in the overall list 
};

struct task* create_task(const char* task_about) {  //gives back the address of newly created task node
    struct task* newnode = (struct task*)malloc(sizeof(struct task)); // allocating memory for a new task 
    strcpy(newnode->task_about, task_about);  //copying task description using strcpy 
    newnode->next = NULL; //this the last node/only node for now in the list
    return newnode; //returns pointer to newly-created  tasknode is returned 
}

struct category* create_category(const char* category_name) {
    struct category* newnode = (struct category*)malloc(sizeof(struct category));
    strcpy(newnode->category_name, category_name); //copying name of the category using strcpy into the category_name field of newly created node
    newnode->task_list = NULL; // The beginning of list is empty
    newnode->next = NULL; // The newnode is not linked/connected to any other nodes yet
    return newnode; //address of newly-created category node is returned
}

struct category* find_category(struct category* head, const char* category_name) {
    struct category* node1 = head;
    while (node1 != NULL && strcmp(node1->category_name, category_name) != 0) {// keep moving to next node until you reach to the end of the list or find the name of the category you're looking for
        node1 = node1->next;
    }
    return node1;//if category is found, returning pointer to that category
}

bool saveTodoTask(task* task) {// functions saves a single task to the file todoListManager.txt
    ofstream tasksOutputfile{"todoListManager.txt", ios::app};//opening the file for output using an offstream object tasksOuputFile associated with todoListManager.txt

    if (!tasksOutputfile) {
        cerr << "Output file could not be opened" << endl;
        return false;
    }

    tasksOutputfile << quoted(task->task_about) << endl;//puts double quotations around the task description i.e. "Do homework"
    tasksOutputfile.close();// Closing file to free resources
    return true; //Returns true if saving is successful
}
void add_task(struct category* category_ptr, const char* task_about) {
    struct task* new_task = create_task(task_about);//Creates a new task node using helper function create_task()
    new_task->next = category_ptr->task_list; //adding new task at the beginning of the list 
    category_ptr->task_list = new_task;//updates category list to start with the new task
     saveTodoTask(new_task);
}

void delete_task(struct category* category_ptr, const char* task_about) {
    struct task* node2 = category_ptr->task_list;//node2 will move through task list to find the task
    struct task* prev = NULL;//keeps track of previous task, needed when deleting a node that is not the first
    while (node2 != NULL && strcmp(node2->task_about, task_about) != 0) {//loop searches through task list ,stops when it finds task with matching description or it reaches end of the list
        prev = node2;
        node2 = node2->next;
    }
    if (node2 != NULL) { //only proceed (delete the task) if we found the task 
        if (prev == NULL) { //if prev is still NULL , the first task has to be deleted
            category_ptr->task_list = node2->next;//move category's task list pointer to second task
        } else {
            prev->next = node2->next;
        }
        free(node2);//deleting the node from memory to prevent a memory leak
    }
}

int count_task(struct category* head) {
    int count = 0;
    struct category* node1 = head;
    while (node1 != NULL) {
        struct task* task_node = node1->task_list;
        while (task_node != NULL) {
            count++;
            task_node = task_node->next;
        }
        node1 = node1->next;
    }
    return count;
}

void display_task_by_category(struct category* head) {
    struct category* node1 = head;
    while (node1 != NULL) {
        cout << "Category: " << node1->category_name << endl;
        struct task* task_node = node1->task_list;
        while (task_node != NULL) {
            cout << " -> Task: " << task_node->task_about << endl;
            task_node = task_node->next;
        }
        node1 = node1->next;
    }
}

int main() {
    struct category* categories = NULL;
    int choice;
    do {
        cout << "TO-DO LIST MENU \n";
        cout << " 1. ADD CATEGORY \n";
        cout << " 2. ADD TASK \n";
        cout << " 3. DELETE TASK \n";
        cout << " 4. DISPLAY CATEGORY BY TASK \n";
        cout << " 5. COUNT ALL OF THE TASKS \n";
        cout << " 6. EXIT \n";
        cout << " GET STARTED NOW! \n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                char name_category[100];
                cout << "Enter name of the category: ";
                cin >> name_category;
                struct category* new_category = create_category(name_category);
                new_category->next = categories;
                categories = new_category;
                break;
            }
            case 2: {
                char category_name[100], task_about[100];
                cout << "Enter the name of the category: ";
                cin >> category_name;
                cout << "Enter the task: ";
                cin>> ws;
                cin.getline(task_about, 100);
                struct category* node1 = find_category(categories, category_name);
                if (node1 != NULL) {
                    add_task(node1, task_about);
                } else {
                    cout << "Category is NOT found! Create a category by entering 1.\n";
                }
                break;
            }
            case 3: {
                char category_name[100], task_about[100];
                cout << "Enter the name of the category: ";
                cin >> category_name;
                cout << "Enter the name of the task you want to delete: ";
                cin >> ws;
                cin.getline(task_about, 100);
                struct category* node1 = find_category(categories, category_name);
                if (node1 != NULL) {
                    delete_task(node1, task_about);
                } else {
                    cout << "Sorry! The category is NOT found!!\n";
                }
                break;
            }
            case 4:
                display_task_by_category(categories);
                break;
            case 5:
                cout << "Total number of tasks: " << count_task(categories) << endl;
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "INVALID CHOICE! PLEASE TRY AGAIN!\n";
        }
    } while (choice != 6);
    
    return 0;
}
