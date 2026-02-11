#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define MAX length of record and names
#define MAX_RECORD_LENGTH 100
#define MAX_NAME_LENGTH 50

// defining our Record struct
typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    int isPresent;
} Record;

// Initializing an array of struct we defined above
Record attendance[MAX_RECORD_LENGTH];
int recordCount = 0; // number of the record present

// function to add a record
void addRecord()
{
    if (recordCount >= MAX_RECORD_LENGTH)
    {
        printf("Cannot add record, List is full!\n");
        return;
    }
    Record newRecord;
    printf("Enter Student ID: ");
    scanf("%d", &newRecord.id);
    // Checks if a student with the same id already occurs
    for (int i = 0; i < recordCount; i++)
    {
        if (attendance[i].id == newRecord.id)
        {
            printf("A Student with the same ID already exists!\n\n");
            return;
        }
    }
    // flush leftover newline
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    printf("Enter Student Name: ");
    fgets(newRecord.name, MAX_NAME_LENGTH, stdin);
    newRecord.name[strcspn(newRecord.name, "\n")] = '\0';
    // checking if the user input 0 or 1 only.
    do
    {
        printf("Enter 1 if present and 0 if absent: ");
        scanf("%d", &newRecord.isPresent);
    } while (newRecord.isPresent != 0 && newRecord.isPresent != 1);

    printf("\n\n Record Added Successfully!\n\n");
    attendance[recordCount] = newRecord;
    recordCount++;
}

// function to display all the records
void displayRecord()
{
    if (recordCount <= 0)
    {
        printf("Record is currently Empty!\n");
        return;
    }
    printf("%-5s %-20s %-7s\n", "ID", "Name", "Remark");
    printf("----------------------------------------\n");
    for (int i = 0; i < recordCount; i++)
    {
        printf("%-5d %-20s %-7s\n", attendance[i].id, attendance[i].name, attendance[i].isPresent ? "Present" : "Absent");
        ;
    }
    printf("\n");
}

// function to search for a specific record using an ID
void searchRecord()
{
    int s_id;
    printf("Enter Record ID: ");
    scanf("%d", &s_id);
    for (int i = 0; i < recordCount; i++)
    {
        if (attendance[i].id == s_id)
        {
            printf("Record Found!\n");
            printf("Student ID: %d\n", attendance[i].id);
            printf("Student Name: %s\n", attendance[i].name);
            printf("Remark: %s\n\n", attendance[i].isPresent ? "Present" : "Absent");
            return;
        }
    }
    printf("Record Not Found\n\n");
}

// delete a record with an ID
void deleteRecord()
{
    int s_id;
    printf("Enter the ID you wanna delete: ");
    scanf("%d", &s_id);
    for (int i = 0; i < recordCount; i++)
    {
        if (attendance[i].id == s_id)
        {
            for (int j = i; j < recordCount - 1; j++)
            {
                attendance[j] = attendance[j + 1];
            }
            recordCount--;
            printf("Record Deleted!\n\n");
            return;
        }
    }
}

int main()
{

    int choice;

    // App loop
    while (1)
    {
        printf("Attendance Monitoring\n");
        printf("=====================\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            displayRecord();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid Choice Motherfucker!\n");
        }
    }

    return 0;
}