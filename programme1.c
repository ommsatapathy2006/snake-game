#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/*
 Snake Water Gun:
  - s = snake
  - w = water
  - g = gun
 Rules:
  - Snake (s) drinks Water (w) -> Snake wins
  - Water (w) rusts Gun (g) -> Water wins
  - Gun (g) kills Snake (s) -> Gun wins
*/

char computer_choice_char() {
    int r = rand() % 3; // 0,1,2
    if (r == 0) return 's';
    if (r == 1) return 'w';
    return 'g';
}

const char* name_of(char c) {
    if (c == 's') return "Snake";
    if (c == 'w') return "Water";
    if (c == 'g') return "Gun";
    return "Unknown";
}

/* Return: 1 if player wins, -1 if computer wins, 0 if tie, 2 if invalid */
int decide_winner(char player, char comp) {
    if (player != 's' && player != 'w' && player != 'g') return 2;
    if (player == comp) return 0;
    // rules
    if (player == 's' && comp == 'w') return 1;
    if (player == 'w' && comp == 'g') return 1;
    if (player == 'g' && comp == 's') return 1;
    // otherwise computer wins
    return -1;
}

int main(void) {
    srand((unsigned) time(NULL));
    printf("=== Snake Water Gun ===\n");
    printf("Choices: s = Snake, w = Water, g = Gun\n");
    printf("Type 'q' to quit at any time.\n\n");

    int player_score = 0, comp_score = 0, rounds_played = 0;
    char input[32];

    while (1) {
        printf("Enter your choice (s/w/g) or 'q' to quit: ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("\nInput error. Exiting.\n");
            break;
        }

        // remove newline
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0) {
            printf("No input detected. Try again.\n");
            continue;
        }

        // take first non-space character
        char c = '\0';
        for (size_t i = 0; i < strlen(input); ++i) {
            if (!isspace((unsigned char)input[i])) { c = tolower((unsigned char)input[i]); break; }
        }

        if (c == 'q') {
            printf("Quitting game.\n\n");
            break;
        }

        char comp = computer_choice_char();
        int result = decide_winner(c, comp);

        if (result == 2) {
            printf("Invalid choice '%s'. Please enter s, w, or g.\n", input);
            continue;
        }

        rounds_played++;
        printf("You chose: %s\tComputer chose: %s\n", name_of(c), name_of(comp));

        if (result == 0) {
            printf("Result: It's a tie!\n");
        } else if (result == 1) {
            player_score++;
            printf("Result: You win this round!\n");
        } else {
            comp_score++;
            printf("Result: Computer wins this round!\n");
        }

        printf("Score -> You: %d  Computer: %d  (Rounds: %d)\n\n",
               player_score, comp_score, rounds_played);
    }

    printf("Final Score after %d rounds -> You: %d  Computer: %d\n", rounds_played, player_score, comp_score);
    if (player_score > comp_score) {
        printf("Overall: You win! Congrats 🎉\n");
    } else if (player_score < comp_score) {
        printf("Overall: Computer wins. Better luck next time!\n");
    } else {
        printf("Overall: It's a draw.\n");
    }
// hello  everybody I want to reveal my gf in this code ,her name is sai shree
    printf("Thanks for playing!\n");
    return 0;
 }
