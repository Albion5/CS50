#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int get_winner(string w1, string w2)

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    string winner = get_winner(word1, word2)
}

int compute_score(string word)
{
    int score = 0;
    char current;
    char char_value = 0;

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

}