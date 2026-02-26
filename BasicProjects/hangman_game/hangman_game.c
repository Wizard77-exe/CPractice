#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDS_NUM 20
#define MAX_WORD_LEN 20

// ARRAY OF WORDS
char words[WORDS_NUM][MAX_WORD_LEN] = {
    "CLOUD", "MANGO", "BURGER", "GUITAR", "PUZZLE", "RHYTHM", "FLOWER", "CASTLE", "BANANA", "MONKEY", "COFFEE",
    "PHONE", "WALLET", "SPORTS", "DANCE", "FROZEN", "WIZARD", "PLANET", "BURGER", "KEYBOARD"};

unsigned int currIndex = 0;

void printAsciiBanner()
{
    // ANSI color codes
    const char* RED = "\x1b[31m";
    const char* YELLOW = "\x1b[33m";
    const char* CYAN = "\x1b[36m";
    const char* RESET = "\x1b[0m";

    printf("%s", CYAN);

    printf("  _    _                                           _             \n");
    printf(" | |  | |                                         | |            \n");
    printf(" | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __ __| | ___  _ __  \n");
    printf(" |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '__/ _` |/ _ \\| '_ \\ \n");
    printf(" | |  | | (_| | | | | (_| | | | | | | (_| | | | (_| | (_) | | | |\n");
    printf(" |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_|  \\__,_|\\___/|_| |_|\n");
    printf("                      __/ |                                       \n");
    printf("                     |___/                                        \n");

    printf("%s", YELLOW);
    printf("\n                WELCOME TO HANGMAN GAME!\n\n");
    printf("%s", RED);
    printf("                Guess letters carefully or the man might hang!\n\n");
    printf("%s", RESET);

    printf("%s", RED);
    printf("  _______\n");
    printf("  |     |\n");
    printf("  |     O\n");
    printf("  |    /|\\\n");
    printf("  |    / \\\n");
    printf("__|__\n");
    printf("%s", RESET);
    printf("\nLet's see if you can save the man!\n\n");
}

void flushInput()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void setMask(char *mask, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        mask[i] = '_';
    }
    mask[len] = '\0';
}

void writeMask(const char *mask)
{
    printf("Hidden Word: ");
    while (*mask)
    {
        printf("%c", *mask);
        mask++;
    }
    printf("\n");
}

int checkGuess(const char *word, char guess, char *mask)
{
    int correctGuess = 0;
    guess = toupper(guess);
    while (*word)
    {
        if (guess == *word)
        {
            *mask = guess;
            correctGuess = 1;
        }
        word++;
        mask++;
    }
    if (correctGuess)
    {
        return 1;
    }
    return 0;
}

int checkMask(const char *mask)
{
    while (*mask)
    {
        if (*mask == '_')
        {
            return 0;
        }
        mask++;
    }
    return 1;
}

void drawHangman(int wrongGuesses)
{
    printf("\x1b[31m************************\n");
    switch (wrongGuesses)
    {
    case 0:
        printf("\n\n\n\n\n");
        break;
    case 1:
        printf("\n\n\n\n\n_____\n");
        break;
    case 2:
        printf("  |\n  |\n  |\n  |\n__|__\n");
        break;
    case 3:
        printf("  _______\n  |     |\n  |\n  |\n  |\n__|__\n");
        break;
    case 4:
        printf("  _______\n  |     |\n  |     O\n  |\n  |\n__|__\n");
        break;
    case 5:
        printf("  _______\n  |     |\n  |     O\n  |     |\n  |\n__|__\n");
        break;
    case 6:
        printf("  _______\n  |     |\n  |     O\n  |    /|\\\n  |\n__|__\n");
        break;
    case 7:
        printf("  _______\n  |     |\n  |     O\n  |    /|\\\n  |    / \\\n__|__\n");
        break;
    }
    printf("************************\n\x1b[0m");
    fflush(stdout);
}

int main()
{
    char guess;
    char *currWord = words[currIndex];
    int wrongGuess = 0;

    char mask[MAX_WORD_LEN + 1];
    // strcpy(mask, currWord);
    setMask(mask, strlen(currWord));

    printf("WELCOME TO HANGMAN GAME!\n");
    printAsciiBanner();
    printf("<<Press 0 to exit game>>\n\n");
    // Game Logic
    do
    {
        drawHangman(wrongGuess);
        writeMask(mask);

        printf("Enter your guess: ");
        scanf(" %c", &guess);
        flushInput();

        if (!checkGuess(currWord, guess, mask))
        {
            wrongGuess++;
        }

        if (wrongGuess >= 7)
        {
            drawHangman(wrongGuess);
            if (currIndex >= WORDS_NUM)
            {
                printf("End of game! You finished all words.\n");
                break;
            }
            printf("Game Over! The word was: %s\n", currWord);
            currIndex++;
            wrongGuess = 0;
            currWord = words[currIndex];
            setMask(mask, strlen(currWord));
        }

        if (checkMask(mask))
        { // player guessed the word
            printf("The Word is %s!\n", currWord);
            printf("You Win!\n");

            currIndex++;
            if (currIndex >= WORDS_NUM)
            { // all words finished
                printf("Congratulations! You finished all words.\n");
                break; // exit the game
            }

            currWord = words[currIndex];     // move to next word
            setMask(mask, strlen(currWord)); // reset mask
            wrongGuess = 0;
        }
    } while (guess != '0');
    return 0;
}