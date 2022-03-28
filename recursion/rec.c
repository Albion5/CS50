#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

void draw(int n)
{
    if (n <= 0 | n > 25)
    {
        return;
    }

    draw(n - 1);

    char current = 96 + n;

    for (int i = 0; i < n; i++)
    {
        printf("%c", current);
    }


    printf("\n");
}