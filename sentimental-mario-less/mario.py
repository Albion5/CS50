# TODO
from cs50 import get_int

def check_height(number):
    return number >= 1 and number <= 8

def build(height):

    for i in range(1, height + 1):
        n_spaces = height - i
        print((n_spaces * " ") + ("#" * i))

height = 0
while not check_height(height):
     height = get_int("Height: ")

build(height)
