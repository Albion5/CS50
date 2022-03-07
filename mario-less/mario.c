#include <cs50.h>
#include <stdio.h>

void build(int size);

int main(void)
{
    // Initialize the height variable
    int height;
    // Promt the user to enter the height between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

    build(height);

}

void build(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf(" ");
            printf("#");
        }
        printf("\n");
    }

}
