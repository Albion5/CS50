# TODO
from cs50 import get_string

# Counts the number of letters in a string
def count_letters(text):
    sum = 0
    n = len(text)
    for i in range(n):
        current = text[i]
        if ((current >= 'a' and current <= 'z') or (current >= 'A' and current <= 'Z')):
            sum = sum + 1
    return sum

# Counts the number of words in a string
def count_words(text):
    sum = 0
    n = len(text)
    for i in range (n):
        current = text[i]
        if (current == ' '):
            sum = sum + 1

    return sum + 1

# Counts the number of sentences in a string
def count_sentences(text):
    sum = 0
    n = len(text)
    for i in range(n):
        current = text[i]
        if (current == '.' or current == '?' or current == '!'):
            sum = sum + 1

    return sum

# Counts the average number of a per 100 b
def count_average(a, b):
    return a / (b * 1.0) * 100

# Counts the index of a text
def test_text(text):
    # First count the number of letters, words and sentences in a string
    letters = count_letters(text)

    words = count_words(text)

    sentences = count_sentences(text)

    # Then count the average number of letters per 100 words
    av_letters = count_average(letters, words)

    # Then count the average number of sentences per 100 words
    av_sentences = count_average(sentences, words)

    # Finally count The Coleman-Liau index of a text
    index = round(0.0588 * av_letters - 0.296 * av_sentences - 15.8)

    return index

def main():
    # Ask user to enter a text
    user_text = get_string("Text: ")

    # Run readability test and save the result in a variable grade_level
    grade_level = test_text(user_text)

    # Print the result of testing depending on the interval to which it belongs
    # If the result is very low
    if (grade_level < 1):
        print("Before Grade 1")

    # If the result is very high
    elif (grade_level >= 16):
        print("Grade 16+")

    # If the resul is ok
    else:
        print(f"Grade {grade_level}")

if __name__ == "__main__":
    main()
