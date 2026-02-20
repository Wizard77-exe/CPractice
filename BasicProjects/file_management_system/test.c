#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_FILENAME 255

bool has_special_char(const char *filename)
{
    while (*filename)
    {
        if (ispunct((unsigned char)*filename) && *filename != '-' && *filename != '_' && *filename != '.')
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
int main()
{
    char filename[MAX_FILENAME + 1];

    printf("%s", check_filename(filename, sizeof(filename)));
    return 0;
}