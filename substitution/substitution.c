#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_key(string letters);
void encrypt(string text, string key);
char substitute(char letter, string key);

int main(int argc, string argv[])
{
    // Check the amount of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check the key string
    if (!check_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Promt the user for a string of plain text
    string plaintext = get_string("plaintext: ");

    // Print the encrypted message
    encrypt(plaintext, argv[1]);

}

bool check_key(string letters)
{
    int len = strlen(letters);

    if (len != 26)
    {
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        char current = letters[i];
        if (!isalpha(current))
        {
            return false;
        }
    }

    return true;
}

void encrypt(string text, string key)
{
    //
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];

        if (isalpha(current))
        {
            current = substitute(current, key);
        }

        printf("%c", current);
    }

}

char substitute(char letter, string key)
{
    //
    int position = 0;
    if (islower(letter))
    {
        position = letter - 'a';
    }
    else if (isupper(letter))
    {
        position = letter - 'A';
    }

    char subst_letter = key[position];
    return subst_letter;
}