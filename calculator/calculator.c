#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");
    // 
    int sum = x + y;
    printf("Equals: %i\n", sum);
    printf("%i\n", x + y);
}