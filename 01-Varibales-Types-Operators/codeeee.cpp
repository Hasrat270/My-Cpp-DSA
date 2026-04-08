#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 500

int main() {
    int selec;
    printf("\tPress 1/2/3\n");
    printf("\t1] Sign Up\n");
    printf("\t2] Login\n");
    printf("\t3] Entertainment Mode\n");
    scanf("%d", &selec);

    // ----------------------- SIGN UP -----------------------
    if (selec == 1) {
        char name[50], fname[50], contact[50], id[50], password[50];

        printf("Enter your name: ");
        scanf(" %[^\n]", name);  // allows spaces in name
        printf("Enter your father's name: ");
        scanf(" %[^\n]", fname);
        printf("Enter your contact NO: ");
        scanf(" %[^\n]", contact);
        printf("Enter your ID: ");
        scanf(" %[^\n]", id);
        printf("Enter your password: ");
        scanf(" %[^\n]", password);

        pid_t pid = fork();

        if (pid < 0) {
            printf("Error in fork()\n");
            return 1;
        }

        if (pid == 0) {  // Child process
            FILE *file = fopen("SignUP.txt", "a");
            if (file == NULL) {
                printf("Error opening file in child.\n");
                exit(1);
            }
            fprintf(file, "%s,%s,%s,%s,%s\n", name, fname, contact, id, password);
            fclose(file);
            exit(0);
        } else {  // Parent process
            wait(NULL);  // wait for child to finish writing
            printf("Data successfully saved!\n");
        }
    }

    // ----------------------- LOGIN -----------------------
    else if (selec == 2) {
        int role;
        printf("\tLogin As\n");
        printf("\t1] Teacher\n");
        printf("\t2] Student\n");
        printf("\t3] Admin\n");
        scanf("%d", &role);

        // ---------- STUDENT LOGIN ----------
        if (role == 2) {
            char id[50], pass[50];
            printf("\tEnter ID: ");
            scanf(" %[^\n]", id);
            printf("\tEnter Password: ");
            scanf(" %[^\n]", pass);

            FILE *file = fopen("SignUP.txt", "r");
            if (file == NULL) {
                printf("No users registered yet.\n");
                return 1;
            }

            char line[MAX_LINE_LENGTH];
            bool logged_in = false;

            while (fgets(line, MAX_LINE_LENGTH, file)) {
                char name[50], fname[50], contact[50], file_id[50], file_pass[50];
                if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%s", name, fname, contact, file_id, file_pass) == 5) {
                    if (strcmp(file_id, id) == 0 && strcmp(file_pass, pass) == 0) {
                        logged_in = true;
                        printf("\t----------------------------------------------\n");
                        printf("\t  WELCOME %s\n", name);
                        printf("\t----------------------------------------------\n");

                        printf("\tPress 1 to view Announcements\n");
                        int choice;
                        scanf("%d", &choice);
                        if (choice == 1) {
                            FILE *ann = fopen("announcements.txt", "r");
                            if (ann == NULL) {
                                printf("No announcements yet.\n");
                            } else {
                                char ann_line[MAX_LINE_LENGTH];
                                printf("\n--- Announcements ---\n");
                                while (fgets(ann_line, MAX_LINE_LENGTH, ann)) {
                                    printf("%s", ann_line);
                                }
                                fclose(ann);
                            }
                        }
                        break;
                    }
                }
            }
            fclose(file);

            if (!logged_in) {
                printf("-------- Access Denied --------\n");
            }
        }

        // ---------- TEACHER LOGIN ----------
        else if (role == 1) {
            char id[50], pass[50];
            printf("\tEnter Teacher ID: ");
            scanf(" %[^\n]", id);
            printf("\tEnter Password: ");
            scanf(" %[^\n]", pass);

            // Simple hardcoded teacher (you can later read from file)
            if (strcmp(id, "teacher") == 0 && strcmp(pass, "teacher") == 0) {
                printf("\t----------------------------------------------\n");
                printf("\t  WELCOME Ms. Noushine\n");
                printf("\t----------------------------------------------\n");

                printf("\tPress 1] Make Announcement  2] View Students\n");
                int choice;
                scanf("%d", &choice);

                if (choice == 1) {
                    char announcement[500];
                    printf("\tStart writing announcement: ");
                    scanf(" %[^\n]", announcement);

                    int fd[2];
                    if (pipe(fd) == -1) {
                        printf("Pipe error\n");
                        return 1;
                    }

                    pid_t pid = fork();
                    if (pid == 0) {  // Child writes to pipe
                        close(fd[0]);
                        write(fd[1], announcement, strlen(announcement) + 1);
                        close(fd[1]);
                        exit(0);
                    } else {  // Parent reads and saves
                        close(fd[1]);
                        char readbuffer[500];
                        read(fd[0], readbuffer, sizeof(readbuffer));
                        wait(NULL);

                        FILE *file = fopen("announcements.txt", "a");
                        if (file != NULL) {
                            fprintf(file, "%s\n", readbuffer);
                            fclose(file);
                            printf("Announcement saved!\n");
                        }
                    }
                }

                else if (choice == 2) {
                    FILE *file = fopen("SignUP.txt", "r");
                    if (file == NULL) {
                        printf("No students registered.\n");
                    } else {
                        char line[MAX_LINE_LENGTH];
                        printf("\n--- Registered Students ---\n");
                        while (fgets(line, MAX_LINE_LENGTH, file)) {
                            printf("%s", line);
                        }
                        fclose(file);
                    }
                }
            } else {
                printf("-------- Access Denied --------\n");
            }
        }

        // ---------- ADMIN LOGIN ----------
        else if (role == 3) {
            printf("\t----------------------------------------------\n");
            printf("\t  ADMINISTRATOR ACCESS\n");
            printf("\t----------------------------------------------\n");

            printf("\tPress 1] Show all files\n");
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                system("ls -la");
            }
            // Shutdown/reboot commands REMOVED for safety
            printf("\tOther admin functions disabled for safety.\n");
        }
    }

    // ----------------------- ENTERTAINMENT MODE -----------------------
    else if (selec == 3) {
        printf("\t----------------------------------------------\n");
        printf("\t  Entertainment Playground\n");
        printf("\t----------------------------------------------\n");

        int choice;
        printf("\tPress 1] Cowsay  2] xcowsay  3] Big Text  4] Asciiquarium\n");
        scanf("%d", &choice);

        if (choice == 1) system("cowsay \"Salam!\"");
        else if (choice == 2) system("xcowsay \"Wa Alaikum Assalam\"");
        else if (choice == 3) system("toilet \"ENDED\"");
        else if (choice == 4) system("asciiquarium");
        else printf("Invalid choice\n");
    }

    return 0;
}