#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Initialize the height variable
    int height;
    // Promt the user to enter the height of the pyramid
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

}