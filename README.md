.vscode/
*.exe
*.out
# C++ To-Do List CLI Application

A lightweight command-line To-Do List application built in C++.  
This project demonstrates core programming fundamentals such as file handling, control structures, and modular problem-solving using a real-world use case.

---

##  Overview

This application allows users to manage their daily tasks directly from the terminal. It provides a simple menu-driven interface to add, view, and store tasks persistently using file handling.

The goal of this project is to strengthen C++ fundamentals while building a practical utility application.

---

##  Features

-  Add new tasks  
-  View existing tasks  
-  Save tasks to a file (`.txt`)  
-  Persistent storage (tasks remain after program exit)  
-  Simple CLI-based user interface  

---

##  Built With

- C++
- File Handling (`fstream`)
- Standard Input/Output (iostream)
- Basic control structures (loops, conditionals)

---

##  Project Structure
todoListManager.cpp → Main source code
todoListManager.txt → File used for storing tasks
.gitignore → Ignored files (executables, IDE settings)


##  How to Run

## Step 1: Compile the program
```bash
g++ todoListManager.cpp -o todo

Windows:
todo.exe

Linux / Mac:
./todo

## Key Learnings:
This project helped me understand and practice:

File handling in C++
Working with persistent data storage
Structuring menu-driven CLI applications
Writing clean and maintainable C++ code
Debugging and handling user input

Purpose of the Project:
The purpose of this project is to practice core C++ concepts by building a functional real-world CLI application. It also serves as a foundation for moving toward more advanced topics such as Object-Oriented Programming and Data Structures.


Future Improvements
Add task deletion and editing functionality
Implement task priority levels (High / Medium / Low)
Replace text file storage with structured formats (JSON)
Convert into a fully OOP-based design (classes & objects)
Add search and filter functionality

Note:
This is a beginner-level project, but structured with scalability and real-world practices in mind.


Author:
Zobiah Saleem 

