#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);

int main(void)
{
    string user_text = get_string("Text: ");
    int letters = count_letters(user_text);
    printf("%i\n", letters);
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char current = text[i];
        printf("%c\n", current);
        if  (current >= 'a' && current <= 'z' | current >= 'A' && current <= 'Z')
        {
            sum = sum + 1;
            printf("%i\n", sum);
        }

    }
    return sum;
}