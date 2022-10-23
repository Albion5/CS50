# TODO
from cs50 import get_int

# Calculates the number of digits in a card number
def get_length(number):
    sum = 1
    while (number > 10):
        last_digit = number % 10
        sum = sum + 1
        # Delete the last digit from the number
        number = (number - last_digit) / 10
    # Return the number of digits in a card number
    return sum


# Calculates the checksum of digits in a card number
def get_checksum(number, length):
    sum1 = 0
    sum2 = 0
    for i in range(length):
        # The last digit in a card number
        current_digit = number % 10

        # For every digit at an even position, starting from the end
        if i % 2 != 0:
            # Multiply the digit at an even position by 2
            double_digit = current_digit * 2

            # Check if the product of multiplying is greater than 9
            if double_digit > 9:
                # Add product's digits
                double_digit = double_digit % 10 + double_digit / 10

            # Calculate the sum of digits at an even position
            sum1 = sum1 + double_digit

        # For every digit at an odd position, starting from the end
        else:
            # Calculate the sum of digits at an odd position
            sum2 = sum2 + current_digit


        # Delete the last digit from the number
        number = (number - current_digit) / 10

    # Add two sums
    sum = sum1 + sum2
    return sum


# Returns 1 if the last digit in a checksum is 0
def check_validity(checksum):
    if checksum % 10 == 0:
        return 1
    else:
        return 0


# Returns the card
def get_card(number, length):

    power = length - 2
    denominator = 1

    for i in range(power):
        denominator *= 10

    # Delete all of the digits except the first two
    start_digits = number / denominator
    print(start_digits)
    # Check if it's MASTERCARD
    if (start_digits > 50 and start_digits <= 55):
        return "MASTERCARD"

    # Check if it's AMEX
    elif (start_digits == 34 or start_digits == 37):
        return "AMEX"

    # Check if it's VISA
    elif (start_digits >= 40 and start_digits <= 49):
        return "VISA"

    # Check if it's a different valid card
    else:
        return "INVALID"


card = "INVALID"
# Ask user to enter the card number
card_number = get_int("Credit card number: ")

# Calculate the length of a card number
digits = get_length(card_number)

# Check validity and a type of the card if it's length is 13, 15 or 16 digits
if (digits == 13 or digits == 15 or digits == 16):

    # Check validity according to Luhn’s algorithm
    checksum = get_checksum(card_number, digits)
    validity = check_validity(checksum)
    if validity == 1:
        # Check the type of a valid card
        card = get_card(card_number, digits)

# Print the card
print(card)



