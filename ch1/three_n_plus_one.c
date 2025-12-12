#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int 
n_cycle_length(
    int n
) {
    int cl = 1;

    while (n != 1) {
        if ((n & 1) == 0)
            n >>= 1;
        else
            n = 3*n + 1;        
        cl++;
    }

    return cl;
}

int
max_range_cycle_length(
    int x,
    int y
) {
    int max_cl = 1;

    int i;
    for (i = MIN(x, y); i <= MAX(x, y); i++)
        max_cl = MAX(max_cl, n_cycle_length(i));
    
    return max_cl;
}

int
main() {
    int x, y;

    while (scanf("%d %d", &x, &y) != EOF)
        printf("%d %d %d\n", x, y, max_range_cycle_length(x, y));

    return 0;
}
