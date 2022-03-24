#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_key(string k);
void decipher(string text, int key);
char rotate(char letter, int shift);

int main(int argc, string argv[])
{
    // Check the amount of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check that every character in argv[1] is a digit
    if (!check_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a string to an int
    int key = atoi(argv[1]) % 26;

    // Promt the user for a sting of plaintext
    string plaintext = get_string("plaintext:  ");

    // Print out the encrypted message
    printf("ciphertext: ");
    decipher(plaintext, key);

    printf("\n");
    return 0;

}

// Checks if the string contains only digits
int check_key(string k)
{
    char current;

    // For each char in a string
    for (int i = 0, len = strlen(k); i < len; i++)
    {
        current = k[i];

        // Check if current char doesn't contain a digit
        if (!isdigit(current))
        {
            return 0;
        }
    }

    // Return 1 if all the characters in a string contain digits
    return 1;
}

// Prints every rotated letter in a string
void decipher(string text, int key)
{
    // For each char in a string
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];

        // Check if current char is alphabetical
        if (isalpha(current))
        {
            // Rotate current char using a key
            current = rotate(current, key);
        }

        // Print current char after rotation
        printf("%c", current);
    }
}

//  Rotates a letter to a certain number of positions
char rotate(char letter, int shift)
{
    // Save the new char in an int, because the result may be > 127
    int conv_letter = letter + shift;

    // If the character after the shift is not alphabetical make the substraction

    if (islower(letter))
    {
        if (conv_letter > 'z')
        {
            conv_letter -= 26;
        }
    }
    else
    {
        if (conv_letter > 'Z')
        {
            conv_letter -= 26;
        }
    }

    // Return converted letter as char
    return conv_letter;
}