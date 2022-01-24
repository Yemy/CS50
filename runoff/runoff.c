#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates and score to win
int voter_count;
int candidate_count;
float win_score;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // loop for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the name is of a valid candidate and rank is not 0
        if (strcmp(candidates[preferences[voter][i]].name, name) == 0 && rank > 0)
        {
            return 0;
        }
        // check if the name is of a valid candidate
        else if (strcmp(candidates[i].name, name) == 0)
        {
            // set the current candidate to the voter's voter
            preferences[voter][rank] = i;
            return true;
        }

    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // check ii is not eluminated then increase votes else jump that and continue
    int cheker = 0;
    for (int i = 0; i < voter_count; i++)
    {
        if (!candidates[preferences[i][cheker]].eliminated)
        {
            candidates[preferences[i][cheker]].votes++;
            cheker = 0;
        }
        else
        {
            cheker++;
            i--;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int won;
    win_score = voter_count / 2;
    won = win_score;
    if (win_score == won)
    {
        win_score++;
    }
    else
    {
        win_score = ceil(win_score);
    }
    //  for each candidate sum the 1st choices
    // if candidates[i].votes > voters / 2; win then quit
    // else call find_min then is_tie if so everyone wins else eliminate min
    // then tabulate next rank to candidate/s
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes >= win_score)
        {
            printf("%s\n", candidates[j].name);
            return 1;
        }
    }
    return 0;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_CANDIDATES;
    // find the minimum vote count
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            continue;
        }
        else if (candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            continue;
        }
        else if (min == candidates[i].votes)
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            continue;
        }
        else if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}