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
    // Call the funtion to build the pyramid of a certain height
    build(height);

}

// Builds the pyramid of a certain height
void build(int size)
{
    // For each row
    for (int i = 1; i < size + 1; i++)
    {
        int spaces = size - i;
        // Spaces for each column
        for (int j = 0; j < spaces; j++)
        {
            printf("*");
        }
        // Hashes for each column
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}
