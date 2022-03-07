#include <cs50.h>
#include <stdio.h>

void build(int rows);

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

void build(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int dots = rows - i;
        int bricks = rows - dots;

        for (int j = 0; j < dots; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < bricks; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}
