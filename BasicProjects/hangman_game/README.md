# HANGMAN GAME
Hangman game is a popular game where a player guesses a letter, and if a letter is in the word, the letter will show up on its 
position in the word
```bash
# let's say the word is CLOUD
_ _ _ _ _ 

# user guesses 'O'
_ _ O _ _

# user guesses 'D'

_ _ O _ D

# and that goes on.
```
---
# Needed Modules
1. <stdio.h>
2. <stdlib.h>
3. <string.h>
4. <ctype.h>
---
# Example Output
1. Welcome
```bash
WELCOME TO HANGMAN GAME!
  _    _                                           _
 | |  | |                                         | |
 | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __ __| | ___  _ __
 |  __  |/ _` | '_ \ / _` | '_ ` _ \ / _` | '__/ _` |/ _ \| '_ \
 | |  | | (_| | | | | (_| | | | | | | (_| | | | (_| | (_) | | | |
 |_|  |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_|  \__,_|\___/|_| |_|
                      __/ |
                     |___/

                WELCOME TO HANGMAN GAME!

                Guess letters carefully or the man might hang!

  _______
  |     |
  |     O
  |    /|\
  |    / \
__|__

Let's see if you can save the man!

<<Press 0 to exit game>>
```
2. Sample Guessing
```bash
<<Press 0 to exit game>>

************************





************************
Hidden Word: _____
Enter your guess: c
************************





************************
Hidden Word: C____
Enter your guess: o
************************





************************
Hidden Word: C_O__
Enter your guess:
```
3. Sample Win
```bash
Hidden Word: CLOU_
Enter your guess: d
The Word is CLOUD!
You Win!
```
4. Sample Game Over
```bash
Hidden Word: ____O
Enter your guess: s
************************
  _______
  |     |
  |     O
  |    /|\
  |    / \
__|__
************************
Game Over! The word was: MANGO
```