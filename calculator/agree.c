#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promt user to agree
    char c = get_char("Do you agree? ");

    // Check whether user agreed
    if (c == 'y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'n')
    {
        printf("Not agreed.\n");
    }
}