#include <cs50.h>
#include <stdio.h>

decrypt(string text, int key);

int main(int argc, string argv[])
{
    string plaintext = get_string("plaintext: ");
    printf("%i\n",argc);
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string ciphertext = decrypt(plaintext, argc);

    printf("ciphertext: ");
}