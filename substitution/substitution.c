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

    // Create an array for letters of an alphabet
    char alphabet[26];
    int position = 0;

    // Put on each position of an array char '?'
    for (int i = 0; i < 26; i ++)
    {
        alphabet[i] = '?';
    }

    // For each char in key string
    for (int i = 0; i < len; i++)
    {
        // Check that current char is alphabetical
        char current = letters[i];

        if (!isalpha(current))
        {
            return false;
        }

        // Check that current char appears only once in a key
        position = toupper(current) - 'A';

        if (alphabet[position] != '?')
        {
            return false;
        }

        // Add current char to an array depending on it's position in the alphabet
        alphabet[position] = current;
    }

    // Return true if the key is valid
    return true;
}

// Substitute each letter in a string using a key and print the result
void encrypt(string text, string key)
{
    // For each char in a string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];

        // Substitute current char if it's alphabetical
        if (isalpha(current))
        {
            current = substitute(current, key);
        }

        // Print substituted char
        printf("%c", current);
    }
}

// Substitute a letter using a key
char substitute(char letter, string key)
{
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