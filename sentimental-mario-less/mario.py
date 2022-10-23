# TODO
from cs50 import get_int

def check_height(number):
    return number >= 1 and number <= 8

def build(height):
    n_spaces = height - 1
    for i in range(height):
        print((n_spaces * " ") + ("#" * (i + 1)))
        n_spaces -= 1

height = 0
while not check_height(height):
     height = get_int("Height: ")

build(height)
