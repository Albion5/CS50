#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int test_text(string text);

int main(void)
{
    // Ask user to enter a text
    string user_text = get_string("Text: ");

    // Check the grade level of the text and save the result in a variable grade_level
    int grade_level = test_text(user_text);

    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if  ((current >= 'a' && current <= 'z') | (current >= 'A' && current <= 'Z'))
        {
            sum = sum + 1;
        }

    }
    return sum;
}

int count_words(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if  (current == ' ')
        {
            sum = sum + 1;
        }

    }
    return sum + 1;
}

int count_sentences(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];

        if  (current == '.' | current == '?' | current == '!')
        {
            sum = sum + 1;
        }

    }
    return sum;
}

int test_text(string text)
{
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float av_letters = letters / (words * 1.0) * 100;

    float av_sentences = sentences / (words * 1.0) * 100;

    int index = round(0.0588 * av_letters - 0.296 * av_sentences - 15.8);

    return index;
}