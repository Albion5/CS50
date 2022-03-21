#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int get_winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    int winner = get_winner(score1, score2);

    if (!winner)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", winner);
    }
}

int compute_score(string word)
{
    int score = 0;
    char current;
    int char_value = 0;

    // TODO: Compute and return score for string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        current = tolower(word[i]);
        char_value = 0;

        if isalpha(current)
        {
            char_value = POINTS[current - 97];
        }

        score = score + char_value;
    }
    printf("%i\n", score);
    return score;
}

int get_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        return 1;
    }
    else if (score2 > score1)
    {
        return 2;
    }
    return 0;
}
