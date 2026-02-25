#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_NUM 20
#define MAX_WORD_LEN 20

// ARRAY OF WORDS
const char words[WORDS_NUM][MAX_WORD_LEN] = {
    "CLOUD", "MANGO", "BURGER", "GUITAR", "PUZZLE", "RHYTHM", "FLOWER", "CASTLE", "BANANA", "MONKEY", "COFFEE",
    "PHONE", "WALLET", "SPORTS", "DANCE", "FROZEN", "WIZARD", "PLANET", "BURGER", "KEYBOARD"
};

unsigned int currIndex = 0;

void printUnderline(const char *s) {
    printf("Hidden Word: ");
    while(*s) {
        printf("_");
        s++;
    }
    printf("\n");
}

void flushInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void guess() {
    char guessChar;
    const char *word = words[currIndex];
    printUnderline(word);
    //Main thing
    printf("Enter your guess: ");
    scanf("%c", &guessChar);
    flushInput();
    printf("Hidden Word: ");
    while(*word) {
        if(*word == guessChar) {
            printf("%c", guessChar);
        }else{
            printf("_");
        }
        word++;
    }
}

int main() {
    guess();
    return 0;
}