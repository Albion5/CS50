#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_key(string k);
string decipher(string text, int key);
char rotate(char letter, int shift);

int main(int argc, string argv[])
{
    if ((argc != 2) | (!check_key(argv[1])))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]) % 26;
    printf("%i\n", key);

    string plaintext = get_string("plaintext: ");

    string ciphertext = decipher(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

int check_key(string k)
{
    char current;

    for (int i = 0, len = strlen(k); i < len; i++)
    {
        current = k[i];

        if (!isdigit(current))
        {
            return 0;
        }
    }

    return 1;
}

string decipher(string text, int key)
{
    string message = "";

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];
        //printf("%c\n", current);

        if (isalpha(current))
        {
            current = rotate(current, key);
        }

        message += current;
    }

    return message;
}

char rotate(char letter, int shift)
{
    char conv_letter;

    if (islower(letter))
    {
        conv_letter = letter + shift;

    }
    else
    {
        conv_letter = letter + shift;
    }
    printf("%c\n", conv_letter);
    return conv_letter;
}