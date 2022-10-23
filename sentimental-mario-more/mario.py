# TODO
from cs50 import get_int


# Check if height is valid number between 1 and 8
def check_height(number):
    return number >= 1 and number <= 8


# Print a pyramid of a given height, a gap between two parts is 2 spaces
def build(height):
    for i in range(1, height + 1):
        n_spaces = height - i
        print((n_spaces * " ") + ("#" * i) + "  " + ("#" * i))


height = 0
# Keep prompting user untill he enters a valid height
while not check_height(height):
    height = get_int("Height: ")

# Print a pyramid of a given height
build(height)
