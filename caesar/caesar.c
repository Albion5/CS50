#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_key(string k);
string decrypt(string text, int key);

int main(int argc, string argv[])
{
    if ((argc != 2) | (!check_key(argv[1])))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");


    //string ciphertext = decrypt(plaintext, argc);

    printf("ciphertext: \n");
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