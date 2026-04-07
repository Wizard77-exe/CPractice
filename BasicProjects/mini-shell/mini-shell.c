#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 255

int main() {
    char command[MAX_LEN];

    while (1) {
        printf("Mini-shell::> ");
        fgets(command, MAX_LEN, stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) break;

        // fork() echo

        printf("%s\n", command);
    }
    return 0;
}
