#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

// Colors aur UI ke liye ANSI Codes
void clearScreen() { cout << "\033[2J\033[1;1H"; }
void setGreen() { cout << "\033[1;32m"; }
void setBlue() { cout << "\033[1;34m"; }
void setYellow() { cout << "\033[1;33m"; }
void resetColor() { cout << "\033[0m"; }

void drawHeader() {
    setYellow();
    cout << "====================================================" << endl;
    cout << "       CUSTOM CLI SHELL - OPERATING SYSTEMS         " << endl;
    cout << "====================================================" << endl;
    resetColor();
}

void printPrompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    setGreen(); cout << "NhuStudents@CLI"; resetColor();
    cout << ":";
    setBlue(); cout << cwd; resetColor();
    cout << "$ ";
}

int main() {
    string command;
    clearScreen();
    drawHeader();
    cout << "Tip: Try 'ls', 'whoami', 'pwd' or 'exit' to quit.\n" << endl;

    while (true) {
        printPrompt();
        getline(cin, command);

        if (command == "exit") break;
        if (command == "clear") {
            clearScreen();
            drawHeader();
            continue;
        }
        if (command.empty()) continue;

        // Custom handling for 'cd'
        if (command.substr(0, 3) == "cd ") {
            string path = command.substr(3);
            if (chdir(path.c_str()) != 0) {
                cout << "Error: Directory not found." << endl;
            }
            continue;
        }

        // Real Execution logic using Fork/Exec
        pid_t pid = fork();
        if (pid == 0) { // Child
            char* args[] = {(char*)"/bin/sh", (char*)"-c", (char*)command.c_str(), NULL};
            execvp(args[0], args);
            exit(1);
        } else { // Parent
            wait(NULL);
        }
    }
    return 0;
}