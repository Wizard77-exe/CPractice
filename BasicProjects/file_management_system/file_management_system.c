#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
        if (ispunct((unsigned char)*filename) && *filename != '-' && *filename != '_' && *filename != '.' )
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
    bool invalid;
    do
    {
        // gets the filename based on the user's preference
        printf("Enter your desired filename: ");
        fgets(filename, 50, stdin);

        // change the newline character in the end of the filename to a null terminator
        filename[strcspn(filename, "\n")] = '\0';

        // checks if the filename is not allowed or allowed
        invalid = has_special_char(filename);
        // give feedback to user
        if (invalid)
        {
            printf("Filename must not contain special character! \n");
        }
    } while (invalid);

    // Creating a File
    FILE *file = fopen(filename, "w"); // "w" for writing, creates file if not exists
    if (file == NULL)
    {
        printf("Error Creating a File! Try Again!\n");
        return;
    }
    fclose(file); // close the file
}

//Function to write to a file
void append_2_file() 
{
    char filename[50];

    printf("Enter filename: ");
    fgets(filename, 50, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) { //check if file doesn't exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }

    file = fopen(filename, "a");
    // validation
    if (file == NULL) {
        printf("Error in Opening a file\n");
        return;
    }
    char buffer[1000];
    printf("You can only write up to 1000 characters at a time.\n");
    printf("Enter \"q\" to quit.\n");
    while (1) {
        fgets(buffer, 1000, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == 'q') {
            break;
        }
        fprintf(file, strcat(buffer, "\n"));
    }
    fclose(file);
    printf("Successfully Added File Content!\n");
    return;
    
}

void rewrite_file_content() {

    if (true) { //check if file exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }
}

void delete_file() {
    if (true) { //check if file exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }
}

void rename_file() {
    if (true) { //check if file exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }
}
void read_file() {
    if (true) { //check if file exists
        printf("Error 404: File Not Found! XD \n");
        return;
    }
}

int main()
{
    int choice;

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
        clear_stdin_line();

        switch(choice) {
            case 1: create_file(); break;
            case 2: append_2_file(); break;
            case 3: rewrite_file_content(); break;
            case 4: delete_file(); break;
            case 5: rename_file(); break;
            case 6: read_file(); break;
            case 7: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}