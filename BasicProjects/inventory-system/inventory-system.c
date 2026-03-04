#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30
#define BUFFER_SIZE 256
#define FILENAME "inventory.txt"

const char *RED = "\x1b[31m";
const char *YELLOW = "\x1b[33m";
const char *CYAN = "\x1b[36m";
const char *RESET = "\x1b[0m";

void flush_input()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int parseItem(char *line, char *name, int *qty)
{
    char *qpos = strstr(line, "Quantity:"); 
    if (!qpos)
        return 0;

    *qty = atoi(qpos + 9); 

    int len = qpos - (line + 11);  
    strncpy(name, line + 11, len); 
    name[len] = '\0'; 

    while (len > 0 && name[len - 1] == ' ')
    {
        name[--len] = '\0';
    }

    return 1;
}

int isExisting(FILE *file, char *item)
{
    char line[BUFFER_SIZE];
    char name[MAX_LEN];
    int qty;

    rewind(file);
    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        if (parseItem(line, name, &qty))
        {
            if (strcmp(item, name) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

void getItemName(FILE *file, char *item_name)
{
    while (1)
    {
        printf("%sEnter Item Name:%s ", YELLOW, RESET);
        fgets(item_name, MAX_LEN, stdin);
        item_name[strcspn(item_name, "\n")] = '\0';

        if (strlen(item_name) == 0)
        {
            printf("%sWarning:%s Item Name cannot be Empty!\n", RED, RESET);
            continue;
        }

        if (isExisting(file, item_name))
        {
            printf("%sItem Already Exists!\n%s", RED, RESET);
            continue;
        }

        break; // valid input
    }
}

void getQuantity(unsigned int *qty)
{
    while(1) {
        printf("%sEnter Quantity:%s ", YELLOW, RESET);
        if(scanf("%u", qty) != 1) {
            flush_input();
            printf("%sInvalid Input!\n", RED);
            continue;
        }
        if (*qty == 0) {
            printf("%sQuantity Cannot be Zero!%s\n", RED, RESET);
            continue;
        }
        break;
    }
}

void listRecords(FILE *file)
{
    char buffer[BUFFER_SIZE];

    printf("\n");
    printf("==============================================================\n");
    printf("%sINVENTORY LIST%s\n", CYAN, RESET);
    printf("==============================================================\n");
    while (fgets(buffer, BUFFER_SIZE, file) != NULL)
    {
        printf("%s", buffer);
    }
    printf("==============================================================\n");
}

void addItem()
{
    FILE *file = fopen(FILENAME, "a+");
    char item_name[MAX_LEN];
    unsigned int qty;
    if (!file)
    {
        perror("fopen");
        return;
    }
    getItemName(file, item_name);
    getQuantity(&qty);

    fprintf(file, "Item Name: %-30s Quantity: %-10u\n", item_name, qty);
    if (fclose(file) != 0)
    {
        perror("Fclose");
        return;
    }
    printf("%s\nSuccessfully Added an Item%s\n", CYAN, RESET);
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
    listRecords(file);

    if (fclose(file) != 0)
    {
        perror("fclose");
        return;
    }
    printf("%sSuccessfully Displayed Items%s\n", CYAN, RESET);
    printf("==============================================================\n");
    return;
}

int findItem(FILE *file, FILE *temp, char *item_name)
{
    int qty;
    int found = 0;
    char buffer[BUFFER_SIZE];
    char name[MAX_LEN];
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
    return found;
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

    char item_name[MAX_LEN];
    printf("\n%sEnter Item You Want to Delete:%s ", YELLOW, RESET);
    fgets(item_name, MAX_LEN, stdin);
    item_name[strcspn(item_name, "\n")] = '\0';

    int found = findItem(file, temp, item_name);

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
        printf("\n%sItem Not Found!%s\n\n", RED, RESET);
        return;
    }
    else
    {
        printf("\n%sSuccessfully Deleted Item Record!%s\n", CYAN, RESET);
        return;
    }
}

int getNewQuantity(FILE *file, FILE *temp, char *item_name)
{
    int qty;
    int found = 0;
    char name[MAX_LEN];
    char buffer[BUFFER_SIZE];

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
                printf("%sWarning:%s Quantity cannot be Zero!\n", RED, RESET);
                printf("%sEnter New Quantity:%s ", YELLOW, RESET);
                if (scanf("%d", &qty) != 1)
                {
                    printf("Invalid input!\n");
                    flush_input(); // clear stdin
                }
            } while (qty <= 0);
            fprintf(temp, "Item Name: %-30s Quantity: %-10u\n", name, qty);
        }
    }

    return found;
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

    
    char item_name[MAX_LEN];
    

    printf("\n%sEnter the Item Name:%s ", YELLOW, RESET);
    fgets(item_name, MAX_LEN, stdin);
    item_name[strcspn(item_name, "\n")] = '\0';

    int found = getNewQuantity(file, temp, item_name);

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
        printf("\n%sItem Not Found!%s\n", RED, RESET);
        return;
    }
    else
    {
        printf("\n%sSuccessfully Updated Item Record!%s\n", CYAN, RESET);
        return;
    }
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n==============================================================\n");
        printf("%s                Inventory System V 1.0.0%s                  \n", CYAN, RESET);
        printf("==============================================================\n");
        printf("%s[1.]%s Add Item\n", YELLOW, RESET);
        printf("%s[2.]%s Display Items\n", YELLOW, RESET);
        printf("%s[3.]%s Delete Item Record\n", YELLOW, RESET);
        printf("%s[4.]%s Update Item Record\n", YELLOW, RESET);
        printf("%s[0.]%s Exit%s\n", YELLOW, RED, RESET);

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