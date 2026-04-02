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

    while (strcmp(command, "exit") != 0) {
        printf("Mini-shell::> ");
        fgets(command, MAX_LEN, stdin);
        command[strcspn(command, "\n")] = '\0';
    }
    return 0;
}
