import csv
import sys
import re


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    # Create a list for dictionaries of each person in database
    people = []

    with open(sys.argv[1]) as file:
        # Create dict reader object
        reader = csv.DictReader(file)

        # For each new line dict in the csv file
        for person in reader:

            # Add it to people list
            people.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        # Read the first line in a given file
        seq = file.readlines()[0]

    # TODO: Find longest match of each STR in DNA sequence
    # Create a dictionary for STRs
    STRs = []
    # For each key of the first dictionary in people list
    for key, _ in people[0].items():
        # Add that key to STRs list
        STRs.append(key)
    # Delete the key "name" so only STR keys are left
    del STRs[0]

    # Create a dict for an undefined person
    undefined = {}

    # For each STR in STRs list
    for STR in STRs:
        # Add to the dict the longest run of consecutive repeats of the STR in the DNA with STR key
        # Make sure to convert the computed number to str
        undefined[STR] = str(longest_match(seq, STR))

    # TODO: Check database for matching profiles
    # Create a variable with default value in case the person is not in the database
    result = "No match"
    # For each dictionary in people list
    for person in people:
        person_dict = person
        # Save the name to a temporary variable
        name = person_dict["name"]
        # Delete key "name" so the keys of this dict and an undefined dict are the same
        person_dict.pop("name")
        # Compare two dictionaries
        if person_dict == undefined:
            # Update the result if found a match in database
            result = name
            break
    # Print out the result
    print(result)
    return 0


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
