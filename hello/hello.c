#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user 
    string name = get_string("Enter your name here: ");
    printf("Hello, %s!\n", name);
}