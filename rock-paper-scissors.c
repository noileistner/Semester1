#include <stdio.h>

int POINTS_TO_WIN = 2;

int main() {
    char option_player1, option_player2;
    int points_player1 = 0, points_player2 = 0;
    int is_valid_input = 0;

    do {
            printf("Rock! Paper! Scissors! Lizard! Spock!\n");

            // Input for Player 1
            do {
                printf("Player 1: ");
                scanf(" %c", &option_player1);

                if (option_player1 != 's' && option_player1 != 'r' && option_player1 != 'p' && 
                    option_player1 != 'k' && option_player1 != 'l') {
                    printf("Option not valid.\n");
                    is_valid_input = 0;
                } else {
                    is_valid_input = 1;
                }
            } while (!is_valid_input);

            is_valid_input = 0;
            // Input for Player 2
            do {
                printf("Player 2: ");
                scanf(" %c", &option_player2);

                if (option_player2 != 's' && option_player2 != 'r' && option_player2 != 'p' && 
                    option_player2 != 'k' && option_player2 != 'l') {
                    printf("Option not valid.\n");
                    is_valid_input = 0;
                } else {
                    is_valid_input = 1;
                }
            } while (!is_valid_input);

            // Game logic
            switch (option_player1) {
                case 's':
                    if (option_player2 == 's') {
                        printf("Draw!\n");
                    } else if (option_player2 == 'p') {
                        printf("Scissors beats paper.\n");
                        points_player1++;
                    } else if (option_player2 == 'r') {
                        printf("Rock beats scissors.\n");
                        points_player2++;
                    } else if (option_player2 == 'l') {
                        printf("Scissors beats lizard.\n");
                        points_player1++;
                    } else if (option_player2 == 'k') {
                        printf("Spock beats scissors.\n");
                        points_player2++;
                    }
                    break;

                case 'p':
                    if (option_player2 == 's') {
                        printf("Scissors beats paper.\n");
                        points_player2++;
                    } else if (option_player2 == 'p') {
                        printf("Draw!\n");
                    } else if (option_player2 == 'r') {
                        printf("Paper beats rock.\n");
                        points_player1++;
                    } else if (option_player2 == 'l') {
                        printf("Lizard beats paper.\n");
                        points_player2++;
                    } else if (option_player2 == 'k') {
                        printf("Paper beats Spock.\n");
                        points_player1++;
                    }
                    break;

                case 'r':
                    if (option_player2 == 's') {
                        printf("Rock beats scissors.\n");
                        points_player1++;
                    } else if (option_player2 == 'p') {
                        printf("Paper beats rock.\n");
                        points_player2++;
                    } else if (option_player2 == 'r') {
                        printf("Draw!\n");
                    } else if (option_player2 == 'l') {
                        printf("Rock beats lizard.\n");
                        points_player1++;
                    } else if (option_player2 == 'k') {
                        printf("Spock beats rock.\n");
                        points_player2++;
                    }
                    break;

                case 'l':
                    if (option_player2 == 's') {
                        printf("Scissors beats lizard.\n");
                        points_player2++;
                    } else if (option_player2 == 'p') {
                        printf("Lizard beats paper.\n");
                        points_player1++;
                    } else if (option_player2 == 'r') {
                        printf("Rock beats lizard.\n");
                        points_player2++;
                    } else if (option_player2 == 'l') {
                        printf("Draw!\n");
                    } else if (option_player2 == 'k') {
                        printf("Lizard beats Spock.\n");
                        points_player1++;
                    }
                    break;

                case 'k':
                    if (option_player2 == 's') {
                        printf("Spock beats scissors.\n");
                        points_player1++;
                    } else if (option_player2 == 'p') {
                        printf("Paper beats Spock.\n");
                        points_player2++;
                    } else if (option_player2 == 'r') {
                        printf("Spock beats rock.\n");
                        points_player1++;
                    } else if (option_player2 == 'l') {
                        printf("Lizard beats Spock.\n");
                        points_player2++;
                    } else if (option_player2 == 'k') {
                        printf("Draw!\n");
                    }
                    break;
            }
    } while (points_player1 < POINTS_TO_WIN && points_player2 < POINTS_TO_WIN);
    
    if (points_player1 == POINTS_TO_WIN) {
        printf("Player 1 wins the game!\n");
    } else if (points_player2 == POINTS_TO_WIN) {
        printf("Player 2 wins the game!\n");
    }

    return 0;
}
