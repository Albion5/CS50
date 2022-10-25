#include <stdio.h>
#include <cs50.h>

float addition(float number1, float number2);
float multiplication(float number1, float number2);
float substraction(float number1, float number2);
float division(float number1, float number2);

int main(void)
{
    float x = get_float("x: ");
    float y = get_float("y: ");
    char operation = get_char("operation(+, -, /, *): ");

    float result = 0;
    if (operation == '+')
    {
        result = addition(x, y);
    }
    else if (operation == '*')
    {
        result = multiplication(x, y);
    }
    else if (operation == '-')
    {
        result = substraction(x, y);
    }
    else if (operation == '/')
    {
        result = division(x, y);
    }

    printf("%.2f \n", result);
}

float addition(float number1, float number2)
{
    return number1 + number2;
}

float multiplication(float number1, float number2)
{
    return number1 * number2;
}

float substraction(float number1, float number2)
{
    return number1 - number2;
}

float division(float number1, float number2)
{
    return number1 / number2;
}