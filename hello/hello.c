#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user to enter their name
    string name = get_string("Enter your name here: ");
    // Print out the greeting
    printf("Hello, %s!\n", name);
}