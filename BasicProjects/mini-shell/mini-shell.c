#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 255

void print(const char *str) {
    if (*str == '\"') {
        str++;
        while (str) {
            putchar(*str);
            if (*str == '\"') break;
            str++;
        }
    }
}

int main() {
    char command[MAX_LEN];

    while (1) {
        printf("Mini-shell::> ");
        fgets(command, MAX_LEN, stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) break;

        printf("%s\n", command);
    }
    return 0;
}
