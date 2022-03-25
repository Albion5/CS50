#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_key(string letters);
//bool check_duplicates(char letter, string letters);
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
    printf("ciphertext: ");
    encrypt(plaintext, argv[1]);
    printf("\n");

    return 0;

}

// Check that the key is valid
bool check_key(string letters)
{
    // First check that the key is 26 characters long
    int len = strlen(letters);

    if (len != 26)
    {
        return false;
    }

    // Then check that each character in a key is alphabetical and appears only once

    // Create a list for letters of an alphabet
    char alphabet[26];
    int position = 0;

    // Put each item of a list with '?'
    for (int i = 0; i < 26; i ++)
    {
        alphabet[i] = '?';
    }

    for (int i = 0; i < len; i++)
    {
        char current = letters[i];
        if (!isalpha(current))
        {
            return false;
        }
        position = toupper(current) - 'A';

        if (alphabet[position] != '?')
        {
            return false;
        }

        alphabet[position] = current;

    return true;
}

//bool check_duplicates(char letter, string letters)
//{

//}

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
    char subst_letter;
    int position = 0;

    if (islower(letter))
    {
        position = letter - 'a';
        subst_letter = tolower(key[position]);
    }
    else
    {
        position = letter - 'A';
        subst_letter = toupper(key[position]);
    }

    return subst_letter;
}