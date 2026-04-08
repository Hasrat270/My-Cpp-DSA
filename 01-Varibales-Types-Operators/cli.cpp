#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>

using namespace std;

// Prompt ko real look dene ke liye (Username@Hostname:Path$)
void print_prompt() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    struct passwd *pw = getpwuid(getuid());
    const char *user = pw ? pw->pw_name : "user";

    cout << "\033[1;32m" << user << "@" << hostname << "\033[0m:" 
         << "\033[1;34m" << cwd << "\033[0m$ ";
}

int main() {
    string input;
    cout << "Welcome to MyCustomShell v1.0" << endl;
    cout << "Type 'exit' to quit." << endl;

    while (true) {
        print_prompt();
        if (!getline(cin, input) || input == "exit") break;
        if (input.empty()) continue;

        // Command parsing
        stringstream ss(input);
        string word;
        vector<string> args;
        while (ss >> word) args.push_back(word);

        // 1. Built-in: cd
        if (args[0] == "cd") {
            string target = (args.size() < 2) ? getenv("HOME") : args[1];
            if (chdir(target.c_str()) != 0) {
                perror("cd failed");
            }
            continue;
        }

        // 2. Built-in: clear (manual check)
        if (args[0] == "cls" || args[0] == "clear") {
            cout << "\033[H\033[J";
            continue;
        }

        // 3. Process Execution (Real Mechanism)
        pid_t pid = fork();
        
        

        if (pid == 0) { // Child Process
            vector<char*> c_args;
            for (auto& s : args) c_args.push_back(&s[0]);
            c_args.push_back(NULL);

            // execvp command ko PATH mein dhoondta hai (e.g., /usr/bin/whoami)
            if (execvp(c_args[0], c_args.data()) == -1) {
                cout << args[0] << ": command not found" << endl;
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Fork failed");
        } else { // Parent Process
            int status;
            waitpid(pid, &status, 0); // Child ke khatam hone ka intezar
        }
    }
    return 0;
}