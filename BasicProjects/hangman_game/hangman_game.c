#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS_NUM 20
#define MAX_WORD_LEN 20

// ARRAY OF WORDS
const char words[WORDS_NUM][MAX_WORD_LEN] = {
    "CLOUD", "MANGO", "BURGER", "GUITAR", "PUZZLE", "RHYTHM", "FLOWER", "CASTLE", "BANANA", "MONKEY", "COFFEE",
    "PHONE", "WALLET", "SPORTS", "DANCE", "FROZEN", "WIZARD", "PLANET", "BURGER", "KEYBOARD"};

unsigned int currIndex = 0;

void flushInput()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}



void guessChar();

int main()
{
    
    return 0;
}