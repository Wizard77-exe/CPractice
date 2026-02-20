#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_FILENAME 255

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

char *check_filename(char *filename, size_t size)
{
    bool invalid;
    do
    {
        printf("Enter your desired filename: ");
        fgets(filename, size, stdin);
        filename[strcspn(filename, "\n")] = '\0';

        if (strlen(filename) == 0)
        {
            printf("Filename cannot be empty!\n");
            continue;
        }

        invalid = has_special_char(filename);
        if (invalid)
            printf("Filename must not contain special character!\n");
    } while (invalid);

    return filename;
}

// Function to create a file
void create_file(void) 
{
    // FILE *filePointer = fopen("filename", "mode");
    char filename[MAX_FILENAME + 1];

    FILE *file = fopen(check_filename(filename, sizeof(filename)), "wx");
    if (!file) {
        perror("fopen");
        return;
    }

    if(fclose(file) != 0) {
        perror("Error closing the file");
        return;
    }
    printf("File Created Successfully!\n");
    return;
}

//Function to write to a file
void append_2_file() 
{
    char filename[MAX_FILENAME + 1];

    FILE *file = fopen(check_filename(filename, sizeof(filename)), "r+");
    if (!file) { //check if file doesn't exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }

    fseek(file, 0, SEEK_END);

    char buffer[1000];

    printf("You can only write up to 1000 characters at a time.\n");
    printf("Enter \"q\" to quit.\n");

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "q") == 0) 
            break;

        fprintf(file, "%s\n", buffer);
    }

    if (fclose(file) != 0) {
        perror("fclose");
        return;
    }

    printf("Successfully Added File Content!\n");
    return;
    
}

void rewrite_file_content() {
    char filename[MAX_FILENAME + 1];

    FILE *file = fopen(check_filename(filename, sizeof(filename)), "r+");
    if (!file) { //check if file doesn't exists
        printf("Error 404: File Not Found! XD\n");
        return;
    }

    //automatic truncate
    if (freopen(filename, "w", file) == NULL) {
        perror("Truncate");
        return;
    }

    char buffer[1000];

    printf("You can only write up to 1000 characters at a time.\n");
    printf("Enter \"q\" to quit.\n");

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "q") == 0) 
            break;

        fprintf(file, "%s\n", buffer);
    }

    if (fclose(file) != 0) {
        perror("fclose");
        return;
    }

    printf("Successfully Rewrote File Content!\n");
    return;
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
    char filename[MAX_FILENAME + 1];
    
    printf("Enter the filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file = fopen(filename, "r");
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
        printf("2. Append Content to a File\n");
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