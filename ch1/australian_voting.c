#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CANDS       20
#define MAX_BALLOTS   1000
#define STRLEN          80
#define BUFLEN          80

char names[MAX_CANDS][STRLEN+1];
int ballots[MAX_BALLOTS][MAX_CANDS];

void 
assign_choice(bool *is_eliminated,
              int ncands,
              int *current_choice,
              int nballots
)
{
    int i, rank, cand;
    for (i = 0; i < nballots; i++) {
        for (rank = current_choice[i]; rank < ncands; rank++) {
            cand = ballots[i][rank];
            if (!is_eliminated[cand]) {
                current_choice[i] = rank;
                break;
            }
        }
    }
}

void
vote_count(int *vote_counts,
           int *current_choice,
           int nballots
)
{
    int i, rank, cand;
    for (i = 0; i < nballots; i++) {
        rank = current_choice[i];
        cand = ballots[i][rank];
        vote_counts[cand]++;
    }
}

int find_max_vote_cand(int *vote_counts,
                       int *current_choice,
                       int nballots
)
{
    int i, rank, cand, max_vote_cand;

    i = 0;
    rank = current_choice[i];
    max_vote_cand = ballots[i][rank];
    for (i = 1; i < nballots; i++) {
        rank = current_choice[i];
        cand = ballots[i][rank];
        if (vote_counts[max_vote_cand] < vote_counts[cand]) {
            max_vote_cand = cand;
        }
    }
    return max_vote_cand;
}

int find_min_vote_cand(int *vote_counts,
                       int *current_choice,
                       int nballots
)
{
    int i, rank, cand, min_vote_cand;

    i = 0;
    rank = current_choice[i];
    min_vote_cand = ballots[i][rank];
    for (i = 1; i < nballots; i++) {
        rank = current_choice[i];
        cand = ballots[i][rank];
        if (vote_counts[cand] < vote_counts[min_vote_cand]) {
            min_vote_cand = cand;
        }
    }
    return min_vote_cand;
}

bool
check_winner(int *vote_counts,
             int max_vote_cand,
             int nballots
)
{
    return vote_counts[max_vote_cand] > nballots / 2;
}

bool
check_tie(int *vote_counts,
          int max_vote_cand,
          int *current_choice,
          int nballots
)
{
    int i, rank, cand;
    for (i = 0; i < nballots; i++) {
        rank = current_choice[i];
        cand = ballots[i][rank];
        if (vote_counts[cand] != vote_counts[max_vote_cand]) {
            return false;
        }
    }
    return true;
}

void
eliminate(bool *is_eliminated,
          int *vote_counts,
          int min_vote_cand,
          int *current_choice,
          int nballots
)
{
    int i, rank, cand;
    for (i = 0; i < nballots; i++) {
        rank = current_choice[i];
        cand = ballots[i][rank];

        if (vote_counts[cand] == vote_counts[min_vote_cand]) {
            is_eliminated[cand] = true;
        }
    }
}

int
main()
{
    int ncases;
    scanf("%d", &ncases);
    getchar();

    while (ncases-- > 0) {
        int i, j;
        char buf[BUFLEN];

        int ncands, nballots;
        bool is_eliminated[MAX_CANDS] = {0};
        int current_choice[MAX_BALLOTS] = {0};

        scanf("%d", &ncands);
        for (i = 0; i < ncands; i++)
            scanf(" %[^\n]%*c", names[i]);

        nballots = 0;
        while (fgets(buf, sizeof(buf), stdin)) {
            char * token;

            if (buf[0] == '\n') break;
            buf[strcspn(buf, "\n")] = '\0';

            j = 0;
            token = strtok(buf, " ");
            while (token != NULL &&
                   nballots < MAX_BALLOTS &&
                   j < ncands
            ) {
                ballots[nballots][j++] = atoi(token) - 1;
                token = strtok(NULL, " ");
            }
            nballots++;
        }

        while(true) {
            int cand;
            int vote_counts[MAX_CANDS] = {0};
            int min_vote_cand, max_vote_cand;

            assign_choice(is_eliminated, ncands, current_choice, nballots);

            vote_count(vote_counts, current_choice, nballots);

            min_vote_cand = find_min_vote_cand(vote_counts, current_choice, nballots);
            max_vote_cand = find_max_vote_cand(vote_counts, current_choice, nballots);

            if(check_winner(vote_counts, max_vote_cand, nballots)) {
                puts(names[max_vote_cand]);
                break;
            }

            if (check_tie(vote_counts, max_vote_cand, current_choice, nballots)) {
                for (cand = 0; cand < ncands; cand++) {
                    if (!is_eliminated[cand] &&
                        vote_counts[cand] == vote_counts[max_vote_cand]
                    ) {
                        puts(names[cand]);
                    }
                }
                break;
            }

            eliminate(is_eliminated, vote_counts, min_vote_cand, current_choice, nballots);

        }
        if (ncases > 0)
            putchar('\n');
    }
    return 0;
}
