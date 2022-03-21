#include <cs50.h>
#include <stdio.h>

int count_letters(string text);

int main(void)
{
    string user_text = get_string("Text: ");
    int letters = count_letters(user_text);

}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if text[i] 

    }
}