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
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (!check_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]) % 26;
    printf("%i\n", key);

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

void decipher(string text, int key)
{

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char current = text[i];
        //printf("%c\n", current);

        if (isalpha(current))
        {
            current = rotate(current, key);
        }

        //message[i] = current;
    }

    printf("\n");
}

char rotate(char letter, int shift)
{
    int conv_letter;
    conv_letter = letter + shift;
    printf("%i\n", conv_letter);

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
    printf("%i\n", conv_letter);

    return conv_letter;
}