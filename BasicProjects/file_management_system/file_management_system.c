#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Custom function to clear the stdin buffer
void clear_stdin_line(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

// Custom function to check if the filename has a special character aside from '- and _'
bool has_special_char(const char *filename)
{
    while (*filename)
    {
        if (ispunct(*filename) && *filename != '-' && *filename != '_')
        {
            return true;
        }
        filename++;
    }
    return false;
}

// Function to create a file
void create_file(void)
{
    // FILE *filePointer = fopen("filename", "mode");
    char filename[50];
    do
    {
        printf("Enter your desired filename: ");
        // clears the stdin buffer
        clear_stdin_line();

        // gets the filename based on the user's preference
        fgets(filename, 50, stdin);

        // give feedback to user
        if (has_special_char(filename))
        {
            printf("Filename must not contain special character! \n");
        }

        // change the newline character in the end of the filename to a null terminator
        filename[strcspn(filename, "\n")] = '\0';
    } while (has_special_char(filename));
    FILE *file = fopen(filename, "w"); // "w" for writing, creates file if not exists
    fclose(file); // close the file
}

int main()
{
    int choice;
    char message[100];

    while (1)
    {
        printf("File Management System V 1.0.0\n");
        printf("==============================\n\n");
        printf("1. Create a File\n");
        printf("2. Write to a File\n");
        printf("3. Rewrite a whole File\n");
        printf("4. Delete a File\n");
        printf("5. Rename a File\n");
        printf("6. Read a File\n");
        printf("7. Exit\n\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);

        /*
        1. Creating a File
        2. Adding Content to a File (Appending)
        3. Rewriting the whole content of a File
        4. Deleting a File
        5. Renaming a File
        6. Reading a File
        */
    }
    return 0;
}