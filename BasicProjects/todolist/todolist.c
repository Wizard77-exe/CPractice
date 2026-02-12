#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TASKS 100
#define MAX_LENGTH 50

char tasks[MAX_TASKS][MAX_LENGTH];
int tasksNumber = 0;
char finishedTasks[MAX_TASKS][MAX_LENGTH];
int finishedTasksCount = 0;

void addTasks()
{
    if (tasksNumber >= MAX_TASKS)
    {
        printf("Cannot add task. Tasks List Already Full!\n");
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    printf("Enter new task: ");
    fgets(tasks[tasksNumber], MAX_LENGTH, stdin);
    tasks[tasksNumber][strcspn(tasks[tasksNumber], "\n")] = '\0';

    tasksNumber++;
    printf("Task Successfully Added!\n");
}

void displayTasks()
{
    if (tasksNumber <= 0)
    {
        printf("There's no Task right now.\n");
        return;
    }
    for (int i = 0; i < tasksNumber; i++)
    {
        printf("%d. %s\n", i + 1, tasks[i]);
    }
}

void deleteTask()
{
    if (tasksNumber <= 0)
    {
        printf("You currently do not have any task!\n");
        return;
    }

    int taskNum;
    printf("Enter the task number you wanna delete: ");
    scanf("%d", &taskNum);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    if (taskNum < 1 || taskNum > tasksNumber)
    {
        printf("Invalid task number!\n");
        return;
    }

    int index = taskNum - 1;

    for (int j = index; j < tasksNumber - 1; j++)
    {
        strcpy(tasks[j], tasks[j + 1]);
    }

    tasksNumber--;
    printf("Task deleted successfully!\n");
}

void markAsDone()
{
    if (tasksNumber <= 0)
    {
        printf("You do not have task listed yet!\n");
        return;
    }

    int tasknum;
    printf("Enter the task Number you wanna mark as done: ");
    scanf("%d", &tasknum);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    if (tasknum < 1 || tasknum > tasksNumber)
    {
        printf("Invalid tasknumber!\n");
        return;
    }

    if (finishedTasksCount >= MAX_TASKS)
    {
        printf("Cannot Mark a task as done. Finished Tasks is full!\n");
        return;
    }

    strcpy(finishedTasks[finishedTasksCount], tasks[tasknum - 1]);
    finishedTasksCount++;
    for (int j = tasknum - 1; j < tasksNumber - 1; j++)
    {
        strcpy(tasks[j], tasks[j + 1]);
    }
    tasksNumber--;
    printf("Task marked as done!\n");
}

void displayFinishedTasks()
{
    if (finishedTasksCount <= 0)
    {
        printf("You currently have no finished task.\n");
        return;
    }
    for (int i = 0; i < finishedTasksCount; i++)
    {
        printf("%d. %s\n", i+1, finishedTasks[i]);
    }
}

void resetFinishedTasks()
{
    memset(finishedTasks, 0, sizeof(finishedTasks));
    finishedTasksCount = 0;
    printf("Successfully Deleted all Finished Tasks.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("TO-DO LIST\n");
        printf("========================\n");
        printf("1. Add Task.\n");
        printf("2. Display Tasks.\n");
        printf("3. Delete Task.\n");
        printf("4. Mark A Task as Done.\n");
        printf("5. Display Finished Tasks.\n");
        printf("6. Reset Finished Tasks.\n");
        printf("7. Exit\n");
        printf("========================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addTasks();
            break;
        case 2:
            displayTasks();
            break;
        case 3:
            deleteTask();
            break;
        case 4:
            markAsDone();
            break;
        case 5: 
            displayFinishedTasks();
            break;
        case 6: 
            resetFinishedTasks();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}