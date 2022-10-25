#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = get_int("How many scores? ");

    int scores[n];
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score: ");
        sum += scores[i];
    }
    printf("Average: %.2f\n", sum / (n * 1.0));
}