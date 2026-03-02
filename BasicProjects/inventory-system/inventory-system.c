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
    } while(qty == 0);


    fprintf(file, "Item Name: %-30s Quantity: %-10u\n", item_name, qty);
    if (fclose(file) != 0)
    {
        perror("Fclose");
        return;
    }
    printf("\x1b[34mSuccessfully Added an Item\x1b[0m\n\n");
    return;
}

void displayItems() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("fopen");
        return;
    }
    
    char buffer[BUFFER_SIZE];
    printf("\n");
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("%s", buffer);
    }

    if (fclose(file) != 0) {
        perror("fclose");
        return;
    }
    printf("\n\x1b[34mSuccessfully Displayed Items\x1b[0m\n\n");
    return;
}

int main()
{
    int choice;
    while(1) {
        printf("Inventory System\n");
        printf("================\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        flush_input();

        switch(choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 0: exit(0); break;
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}