import csv
import sys
import re


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    people = []

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        # For each line in the csv file
        for row in reader:
            # Create a dictionary with keys "team" and "rating" and add to them values
            person = row
            # person["name"] = row["name"]
            # person["AGATC"] = int(row["AGATC"])
            # person["TTTTTTCT"] = int(row["TTTTTTCT"])
            # person["AATG"] = int(row["AATG"])
            # person["TCTAG"] = int(row["TCTAG"])
            # person["GATA"] = int(row["GATA"])
            # person["TATC"] = int(row["TATC"])
            # person["TCTG"] = int(row["TCTG"])
            # Add team dictionary to the teams list
            people.append(person)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        seq = file.readlines()[0]
        print(seq)

    # TODO: Find longest match of each STR in DNA sequence
    #re.findall()
    # TODO: Check database for matching profiles

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
