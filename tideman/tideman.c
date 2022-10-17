#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    print_winner();
    sort_pairs();
    //lock_pairs();
    //print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int strong_cand_index = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int weak_cand_index = ranks[j];
            preferences[strong_cand_index][weak_cand_index]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //
    int swap, win_index, los_index, next_win_index, next_los_index;
    int dif_votes, dif_votes_1;
    swap = 3;
    int end = pair_count;
    printf("Before:\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("winner=%d loser=%d\n", pairs[i].winner, pairs[i].loser);
    }
    while (swap != 0)
    {
        swap = 0;
        for (int cur = 0; cur < end - 1; cur++)
        {
            win_index = pairs[cur].winner;
            los_index = pairs[cur].loser;
            next_win_index = pairs[cur + 1].winner;
            next_los_index = pairs[cur + 1].loser;
            dif_votes = preferences[win_index][los_index] - preferences[los_index][win_index];
            dif_votes_1 = preferences[next_win_index][next_los_index] - preferences[next_los_index][next_win_index];

            if (dif_votes_1 > dif_votes)
            {
                pair temp = pairs[cur];
                pairs[cur] = pairs[cur + 1];
                pairs[cur + 1] = temp;
                swap++;
            }
        }
        end--;
    }
    printf("After:\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("winner=%d loser=%d\n", pairs[i].winner, pairs[i].loser);
    }

    return;
}

bool cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        printf("winner=%d loser=%d\n", pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}