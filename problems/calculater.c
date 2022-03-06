#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promt user for x
    float x = get_float("x: ");

    // Promt user for y
    float y = get_float("y: ");

    // Divide x by y
    float z = x / y;

    // Print out the result
    printf("%.2f\n", z);

}