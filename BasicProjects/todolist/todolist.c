#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 100
#define MAX_LENGTH 50

char tasks[MAX_TASKS][MAX_LENGTH];
int tasksNumber = 0;

void addTasks() {
    if (tasksNumber >= MAX_TASKS) {
        printf("Cannot add task. Tasks Already Full!\n");
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    printf("Enter new task: ");
    fgets(tasks[tasksNumber], MAX_LENGTH, stdin);
    tasksNumber++;
    printf("Task Successfully Added!\n");
}

void displayTasks() {
    if (tasksNumber <= 0) {
        printf("There's no Tasks right now.\n");
        return;
    }
    for (int i = 0; i < tasksNumber; i++) {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

void deleteTask() {
    if (tasksNumber <= 0) {
        printf("You currently do not have any task!\n");
        return;
    }
    int taskNum;
    printf("Enter the task number you wanna delete: ");
    scanf("%d", &taskNum);

    for (int i = 0; i < tasksNumber; i++) {
        if (i == taskNum - 1) {
            for (int j = i; j < tasksNumber - 1; j++) {
                strcpy(tasks[i], tasks[i + 1]);
            }
        }
    }
    return;
}

int main() {
    int choice;

    while(1) {
        printf("TO-DO LIST\n");
        printf("========================\n");
        printf("1. Add Task.\n");
        printf("2. Display Tasks.\n");
        printf("3. Delete Tasks.\n");
        printf("4. Exit\n");
        printf("========================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addTasks(); break;
            case 2: displayTasks(); break;
            case 3: deleteTask(); break;
            case 4: exit(0); break;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}