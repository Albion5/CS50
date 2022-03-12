#include <cs50.h>
#include <stdio.h>

int get_length(long number);
int get_checksum(long number, int length);
int check_validity(int checksum);
string get_card(long number, int length);

int main(void)
{
    string card = "INVALID";
    // Ask user to enter the card number
    long card_number = get_long("Credit card number: ");

    // Calculate the length of a card number
    int digits = get_length(card_number);

    // Calculate the checksum of the digits if their amount is 13, 15 or 16
    if (digits == 13 || digits == 15 || digits == 16)
    {
        int checksum = get_checksum(card_number, digits);
        int validity = check_validity(checksum);
        if (validity == 1)
        {
            card = get_card(card_number, digits);
        }

    }
    printf("%s\n", card);

}

// Calculates the number of digits in a card number
int get_length(long number)
{
    int sum = 1;
    int last_digit;
    while (number > 10)
    {
    last_digit = number % 10;
    sum = sum + 1;
    number = (number - last_digit) / 10;
    }
    return sum;
}

// Calculate the checksum of digits in a card number
int get_checksum(long number, int length)
{
    int sum1 = 0;
    int sum2 = 0;
    int current_digit;
    int double_digit;
    for (int i = 0; i < length; i++)
    {
        // The last digit in a card number
        current_digit = number % 10;

        // For every digit at an even position, starting from the end
        if (i % 2 != 0)
        {
            // Multiply the digit at an even position by 2
            double_digit = current_digit * 2;

            // Check if the product of multiplying is greater than 9
            if (double_digit > 9)
            {
                // Add product's digits
                double_digit = double_digit % 10 + double_digit / 10;
            }
            // Calculate the sum of digits at an even position
            sum1 = sum1 + double_digit;
        }
        // For every digit at an odd position, starting from the end
        else
        {
            // Calculate the sum of digits at an odd position
            sum2 = sum2 + current_digit;
        }

        // Delete the last digit from the number
        number = (number - current_digit) / 10;
    }

    // Add two sums
    int sum = sum1 + sum2;
    return sum;
}

// Returns 1 if the last digit in a checksum is 0
int check_validity(int checksum)
{
    if (checksum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string get_card(long number, int length)
{
    printf("%li\n", number);
    int start_digits = number / 10^(length-2);
    printf("%i\n", start_digits);

    //return "AMEX"
    //return "MASTERCARD"
    if (start_digits == 40)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }

}