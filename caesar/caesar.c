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
    // Check that your key contains digits
    if (!check_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert key to an integer
    int key = atoi(argv[1]) % 26;

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    decipher(plaintext, key);
    //int jo = 'n' + 19;
    //printf("%i\n", jo);

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

// Prints every rotated letter in a string
void decipher(string text, int key)
{

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];

        if (isalpha(current))
        {
            current = rotate(current, key);

        }
        printf("%c", current);
    }

    printf("\n");
}

//  Rotates a letter to a certain number of positions
char rotate(char letter, int shift)
{
    int conv_letter;
    conv_letter = letter + shift;

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

    return conv_letter;
}