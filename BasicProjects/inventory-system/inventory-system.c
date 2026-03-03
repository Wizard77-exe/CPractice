#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30
#define BUFFER_SIZE 256
#define FILENAME "inventory.txt"

void flush_input()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int parseItem(char *line, char *name, int *qty)
{
    char *qpos = strstr(line, "Quantity:"); // returns the pointer to the first occurrence of the substring "Quantity:"
    if (!qpos)
        return 0; // checks if there's a substring "Quantity"

    *qty = atoi(qpos + 9); // converts to integer the value after the "Quantity:". qpos points to Q, + 9, length of "Quantity:"

    int len = qpos - (line + 11);  // gets the length of the name which sits between the line + 11: meaning start of line + 11("Item Name: ") and qpos("Quantity")
    strncpy(name, line + 11, len); // copies the len characters from line + 11 to the name variable.
    name[len] = '\0';              // sets the last character to '\0' because strncpy don't automatically adds a null terminator

    while (len > 0 && name[len - 1] == ' ') // Removes trailing spaces
        name[--len] = '\0';

    return 1;
}

void addItem()
{
    FILE *file = fopen(FILENAME, "a");
    char item_name[MAX_LEN];
    unsigned int qty;
    if (!file)
    {
        perror("fopen");
        return;
    }

    do
    {
        printf("\x1b[31mWarning:\x1b[0m Item Name cannot be Empty!\n");
        printf("\x1b[33mEnter Item Name:\x1b[0m ");
        fgets(item_name, MAX_LEN, stdin);
        item_name[strcspn(item_name, "\n")] = '\0';
    } while (strlen(item_name) == 0);

    do
    {
        printf("\x1b[31mWarning:\x1b[0m Quantity cannot be Zero!\n");
        printf("\x1b[33mEnter Quantity:\x1b[0m ");
        scanf("%u", &qty);
        flush_input();
    } while (qty == 0);

    fprintf(file, "Item Name: %-30s Quantity: %-10u\n", item_name, qty);
    if (fclose(file) != 0)
    {
        perror("Fclose");
        return;
    }
    printf("\x1b[34mSuccessfully Added an Item\x1b[0m\n\n");
    return;
}

void displayItems()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("\n");
    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        printf("%s", buffer);
    }

    if (fclose(file) != 0)
    {
        perror("fclose");
        return;
    }
    printf("\n\x1b[34mSuccessfully Displayed Items\x1b[0m\n\n");
    return;
}

void deleteItem()
{
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp)
    {
        perror("fopen");
        return;
    }

    char buffer[BUFFER_SIZE];
    char name[MAX_LEN];
    char item_name[MAX_LEN];
    printf("Enter Item You Want to Delete: ");
    fgets(item_name, 30, stdin);
    item_name[strcspn(item_name, "\n")] = '\0';

    int qty;
    int found = 0;

    while (fgets(buffer, BUFFER_SIZE, file))
    {
        if (!parseItem(buffer, name, &qty))
        {
            fputs(buffer, temp);
            continue;
        }

        if (strcmp(name, item_name) != 0)
            fputs(buffer, temp);
        else
            found = 1;
    }

    if (fclose(file) != 0)
    {
        perror("fclose file");
        return;
    }
    if (fclose(temp) != 0)
    {
        perror("fclose temp");
        return;
    }

    if (remove(FILENAME) != 0 || rename("temp.txt", FILENAME) != 0)
    {
        perror("File Update");
        return;
    }

    if (!found)
    {
        printf("\n\x1b[31mItem Not Found!\x1b[0m\n\n");
        return;
    }
    else
    {
        printf("\n\x1b[34mSuccessfully Deleted Item Record!\x1b[0m\n\n");
        return;
    }
}

void updateItem()
{
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp)
    {
        perror("fopen");
        return;
    }

    int qty;
    int found = 0;
    char name[MAX_LEN];
    char item_name[MAX_LEN];
    char buffer[BUFFER_SIZE];

    printf("Enter the Item Name: ");
    fgets(item_name, MAX_LEN, stdin);
    item_name[strcspn(item_name, "\n")] = '\0';

    while (fgets(buffer, BUFFER_SIZE, file))
    {
        if (!parseItem(buffer, name, &qty))
        {
            fputs(buffer, temp);
            continue;
        }

        if (strcmp(name, item_name) != 0)
        {
            fputs(buffer, temp);
        }
        else
        {
            found = 1;
            do
            {
                printf("\x1b[31mWarning:\x1b[0m Quantity cannot be Zero!\n");
                printf("\x1b[33mEnter New Quantity:\x1b[0m ");
                if (scanf("%d", &qty) != 1)
                {
                    printf("Invalid input!\n");
                    flush_input(); // clear stdin
                }
            } while (qty <= 0);
            fprintf(temp, "Item Name: %-30s Quantity: %-10u\n", name, qty);
        }
    }

    if (fclose(file) != 0)
    {
        perror("fclose file");
        return;
    }
    if (fclose(temp) != 0)
    {
        perror("fclose temp");
        return;
    }

    if (remove(FILENAME) != 0 || rename("temp.txt", FILENAME) != 0)
    {
        perror("File Update");
        return;
    }

    if (!found)
    {
        printf("\n\x1b[31mItem Not Found!\x1b[0m\n\n");
        return;
    }
    else
    {
        printf("\n\x1b[34mSuccessfully Updated Item Record!\x1b[0m\n\n");
        return;
    }
}

int main()
{
    int choice;
    while (1)
    {
        printf("Inventory System\n");
        printf("================\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Delete Item Record\n");
        printf("4. Update Item Record\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        flush_input();

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            displayItems();
            break;
        case 3:
            deleteItem();
            break;
        case 4: 
            updateItem();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Invalid Choice\n");
        }
        choice = 0;
    }
    return 0;
}