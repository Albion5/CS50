#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promt user for x
    float x = get_user("x: ");

    // Promt user for y
    long y = get_user("y: ");

    // Perform addition
    printf("%li\n", x + y);

}