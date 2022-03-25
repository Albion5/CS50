#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool check_key(string letters);

int main(int argc, string argv[])
{
    // Check the amount of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
    }

    // Check the key string
    if (!check_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
    }

    // Promt the user for a string of plain text

    // Print the encrypted message
}

bool check_key(string letters)
{
    int len = strlen(letters);

    if (len != 26)
    {
        return False;
    }

    for (int i = 0; i < len; i++)
    {
        char current = letters[i];
        if (!isalpha(current))
        {
            return False;
        }
    }

    return True;
}