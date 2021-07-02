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
void lock_pairs(void);
void print_winner(void);
void mergeSort(pair stru[], int min, int max);
void merge(pair stru[], int min, int mid, int max);
bool check_cycle(int start, int end);

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
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check for valid name and update voter's ranks
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // iterate over each ranked candidate from 1st to 2nd last
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        // iterate for each candidate, the sub ranked candidates
        for (int j = i + 1; j < candidate_count; j ++)
            preferences[ranks[i]][ranks[j]] ++;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate over each pair in preferences matrix add pair if a winner and loser
    for (int i = 0; i < candidate_count; i++)
    {
        // iterate for each candidate, the sub ranked candidates
        for (int j = (i + 1); j < candidate_count; j ++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }

            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    mergeSort(pairs, 0, pair_count);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loops through each pairs
    for (int i = 0; i < pair_count; i++)
    {
        // set start and end of "arrow"
        int start = pairs[i].winner;
        int end = pairs[i].loser;

        // if there is no cycle, it records the arrow
        if (check_cycle(start, end))
            locked[start][end] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
                break;

            if (i == (candidate_count - 1))
            {
                printf("%s\n", candidates[j]);
                return;
            }
        }
    }
}


void mergeSort(pair stru[], int min, int max)
{
    int mid = (min + max) / 2;

    if (min != max)
    {
        mergeSort(stru, min, mid);
        mergeSort(stru, mid + 1, max);
        merge(stru, min, mid, max);
    }
    else
        return;
}

void merge(pair stru[], int min, int mid, int max)
{
    int belowMid = mid - min + 1;
    int aboveMid = max - mid;

    pair left[belowMid], right[aboveMid]; // temprary left and right array (working space)

    // copy array to working space
    for (int i = 0; i < belowMid; i++)
        left[i] = stru[min + i];
    for (int j = 0; j < aboveMid; j++)
        right[j] = stru[mid + 1 + j];

    int l = 0, r = 0, t = min; // index of left, right, total to track merging of each half

    // merge left, right based on decreasing strength
    while (l < belowMid && r < aboveMid)
    {
        if (preferences[left[l].winner][left[l].loser] > preferences[right[r].winner][right[r].loser])
        {
            stru[t] = left[l];
            l++;
        }
        else
        {
            stru[t] = right[r];
            r++;
        }
        t++;
    }

    // if only items on left side, fill them in
    while (l < belowMid)
    {
        stru[t] = left[l];
        l++;
        t++;
    }

    // if only items on right side, fill them in
    while (r < aboveMid)
    {
        stru[t] =  right[r];
        r++;
        t++;
    }
}

// recursively call function back to origin of edge / arrow
// returns false if cycle exisits
bool check_cycle(int start, int end)
{
    // base case to terminate recursive function
    // notices about loop if the beginning of the arrow eventually end up at the same as the start
    if (start == end)
        return false;

    // recursive case
    // loops through each candidate to find if arrow eventually end up at the point of origin indicating a cycle
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (i == start)
                return false;
            if (!check_cycle(start, i))
                return false;
        }
    }
    return true;
}
