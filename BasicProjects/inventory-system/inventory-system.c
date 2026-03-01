#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30
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
    printf("\x1b[33mSuccessfully Added an Item\n\x1b[0m");
    return;
}

int main()
{
    addItem();
    return 0;
}