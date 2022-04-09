#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
    return 0;
}

// Update the number of votes for a candidate given a new vote
bool vote(string name)
{
    string participant;

    // Compare the given name with names in a list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        participant = candidates[i].name;

        // Count a new vote if there is a candidate with that name
        if (strcmp(name, participant) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    // If there's no candidate with that name return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Set the highest score to zero
    int win_score = 0;

    // Find the highest score among the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Update the highest score
        if (candidates[i].votes > win_score)
        {
            win_score = candidates[i].votes;
        }
    }

    // Print the names of the candidates with the highest score
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == win_score)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}