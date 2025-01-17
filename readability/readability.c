#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float count_average(int a, int b);
int test_text(string text);

int main(void)
{
    // Ask user to enter a text
    string user_text = get_string("Text: ");

    // Run readability test and save the result in a variable grade_level
    int grade_level = test_text(user_text);

    // Print the result of testing depending on the interval to which it belongs
    // If the result is very low
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    // If the result is very high
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    // If the resul is ok
    else
    {
        printf("Grade %i\n", grade_level);
    }
}

// Counts the number of letters in a string
int count_letters(string text)
{
    int sum = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if ((current >= 'a' && current <= 'z') | (current >= 'A' && current <= 'Z'))
        {
            sum = sum + 1;
        }
    }

    return sum;
}

// Counts the number of words in a string
int count_words(string text)
{
    int sum = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if (current == ' ')
        {
            sum = sum + 1;
        }
    }

    return sum + 1;
}

// Counts the number of sentences in a string
int count_sentences(string text)
{
    int sum = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if (current == '.' | current == '?' | current == '!')
        {
            sum = sum + 1;
        }
    }

    return sum;
}

// Counts the average number of a per 100 b
float count_average(int a, int b)
{
    return a / (b * 1.0) * 100;
}

// Counts the index of a text
int test_text(string text)
{
    // First count the number of letters, words and sentences in a string
    int letters = count_letters(text);

    int words = count_words(text);

    int sentences = count_sentences(text);

    // Then count the average number of letters per 100 words
    float av_letters = count_average(letters, words);

    // Then count the average number of sentences per 100 words
    float av_sentences = count_average(sentences, words);

    // Finally count The Coleman-Liau index of a text
    int index = round(0.0588 * av_letters - 0.296 * av_sentences - 15.8);

    return index;
}