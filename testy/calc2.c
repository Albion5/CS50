#include <stdio.h>
#include <cs50.h>

float calculation(float number1, float number2, char operator);

int main(void)
{
    float x = get_float("x: ");
    float y = get_float("y: ");
    char operation;

    do
    {
        operation = get_char("operation(+, -, /, *): ");
    }
    while ((operation != '+') && (operation != '-') && (operation != '*') && (operation != '/'));


    float result;
    result = calculation(x, y, operation);

    printf("%.2f \n", result);
}

float calculation(float number1, float number2, char operator)
{
    if (operator == '+')
    {
        return number1 + number2;
    }
    else if (operator == '*')
    {
        return number1 * number2;
    }
    else if (operator == '-')
    {
        return number1 - number2;
    }
    else if (operator == '/')
    {
        return number1 / number2;
    }
    else
    {
        return 0;
    }
}
