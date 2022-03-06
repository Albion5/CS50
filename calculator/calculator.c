#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promt user for x and y
    int x = get_int("x: ");
    int y = get_int("y: ");

    // Perform addition and assign the result to a sum variable
    int sum = x + y;
    printf("Equals: %i\n", sum);

    // Perform addition and then print the result
    printf("%i\n", x + y);
}