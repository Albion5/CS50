#include <cs50.h>
#include <stdio.h>

int check_key(string k);
string decrypt(string text, int key);

int main(int argc, string argv[])
{
    if (argc != 2) | !check_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");


    //string ciphertext = decrypt(plaintext, argc);

    printf("ciphertext: ");
}

int check_key(string k)
{
    char current;

    for (int i = 0, len = strlen(string); i < len; i++)
    {
        current = string[i];

        if !is_digit(current)
        {
            return 0;
        }
    }

    return 1;
}