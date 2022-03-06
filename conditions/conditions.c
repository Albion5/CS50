#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("your number: ");
    int y = get_int("your number2: ");
    if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x > y)
    {
        printf("x is not less than y\n");
    }
    else
    {
        printf("x is equal to y\n");
    }

}