#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int test_text(int l, int w, int s);

int main(void)
{
    string user_text = get_string("Text: ");

    int letters = count_letters(user_text);
    int words = count_words(user_text);
    int sentences = count_sentences(user_text);
    int grade_level = test_text(letters, words, sentences);

    printf("Letters: %i, Words: %i, Sentences: %i\n", letters, words, sentences);
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

int test_text(int l, int w, int s)
{
    int av_letters = round(l / (w * 1.0) * 100);
    printf("%i\n", av_letters);
    int av_sentences = round(s / (w * 1.0) * 100);
    printf("%i\n", av_sentences);
    return 1;
}