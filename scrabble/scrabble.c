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

    // Get the number of a player with a higher score or 0 if there is no winner
    int winner = get_winner(score1, score2);

    // Print the winner
    if (!winner)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", winner);
    }
}

// Computes the score for string
int compute_score(string word)
{
    int score = 0;
    char current;
    int char_value = 0;

    // Compute and return score for string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Convert current char to lowercase
        current = tolower(word[i]);

        // Check if current char is a letter
        if isalpha(current)
        {
            // Compute the value of current char
            char_value = POINTS[current - 97];

            // Update the score
            score += char_value;
        }
    }

    return score;
}

// Compares 2 values and returns 1, 2 or 0 dependng on the result of comparison
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
