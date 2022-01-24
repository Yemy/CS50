import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # to store STRs
    STRs = []
    # to store each STR's profile
    profiles = []

    # Read database file
    with open(sys.argv[1]) as database:
        reader = csv.DictReader(database)
        # add STRs starting from the second col to the end
        STRs = reader.fieldnames[1:]
        for STR in reader:
            # Add STR to profiles
            profiles.append(STR)

    # dictionary for sequence file
    seq_count = dict.fromkeys(STRs, 0)

    # Read in sequence file(sequence f DNA)
    with open(sys.argv[2]) as sequence_file:
        # read the first line of txt file
        sequence = sequence_file.readline()
        # Loop over every STRs from the database
        for STR in STRs:
            # Update the Sequence STR dictionary with longest match
            seq_count[STR] = longest_match(sequence, STR)

    # Check if any person has same amount of STR repeats as the input sequence
    for profile in profiles:
        match_count = 0
        for STR in STRs:
            # if max count is not equal to the sequence count of the STR then countue to the next
            if int(profile[STR]) != seq_count[STR]:
                continue
            match_count += 1
        # if match count is equal to the length of the STRs then boom we 've got the match person
        if match_count == len(STRs):
            print(profile['name'])
            sys.exit(0)
    print("No match")
    sys.exit(1)


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
