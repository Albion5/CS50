#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promt user for x and y
    long x = get_long("x: ");
    long y = get_long("y: ");

    // Perform addition using sum variable
    long sum = x + y;
    printf("Equals: %li\n", sum);

    // Perform addition
    printf("%li\n", x + y);
}