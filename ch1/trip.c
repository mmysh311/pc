#include <stdio.h>

#define MAX_MATES 1000
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int costs[MAX_MATES];

int
main() {
    int i;
    int nmates;
    int nbucks, ncents;
    int avg_cost, extra_pennies, total_cost;
    int minex, overavg;

    while (scanf("%d", &nmates) != EOF) {
        if (nmates == 0)
            break;

        total_cost = 0;
        for (i = 0; i < nmates; i++) {
            scanf("%d.%d", &nbucks, &ncents);
            costs[i] = nbucks * 100 + ncents;
            total_cost += costs[i];
        }

        avg_cost = total_cost / nmates;
        extra_pennies = total_cost % nmates;

        minex = 0;
        overavg = 0;
        for (i = 0; i < nmates; i++) {
            if (costs[i] > avg_cost) {
                minex += (costs[i] - avg_cost);
                overavg++;
            }
        }
        /*
         * final distribution: extra_pennies == overavg
         * initial distribution: extra_pennies {<, ==, >} overavg
         */
        minex -= MIN(extra_pennies, overavg);
        printf("$%d.%02d\n", minex / 100, minex % 100);
    }
    return 0;
}
