#include <stdio.h>

void meow(void)
{
    printf("meow\n");
}

int main(void)
{
    for (i = 0; i < 3; i++)
    {
        meow();
    }
}