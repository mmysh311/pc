#include <stdio.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MINE     -1

int field[MAX_ROWS+2][MAX_COLS+2];

void
place_mine(
    int row,
    int col
) {
    int i;
    const int roff[8] = { -1, -1,  0,  1,  1,  1,   0, -1 };
    const int coff[8] = {  0,  1,  1,  1,  0, -1,  -1, -1 };
    
    field[row][col] = MINE;

    for (i = 0; i < 8; i++) {
        int adj_row = row + roff[i];
        int adj_col = col + coff[i];

        if (field[adj_row][adj_col] != MINE) {
            field[adj_row][adj_col]++;
        }
    }
}

void
print_field(
    int nrows,
    int ncols
) {
    int r, c;

    for (r = 1; r <= nrows; r++) {
        for (c = 1; c <= ncols; c++) {
            if (field[r][c] == MINE) {
                printf("*");
            } else {
                printf("%d", field[r][c]);
            }
        }
        printf("\n");
    }
}

int
main() {
    int r, c;
    int nrows, ncols;
    int fno = 0;
    char field_line[MAX_COLS+1];

    while (scanf("%d %d", &nrows, &ncols) != EOF) {
        if (nrows == 0 && ncols == 0)
            break;

        memset(field, 0, sizeof(field));

        for (r = 1; r <= nrows; r++) {
            scanf(" %[^\n]%*c", field_line);

            for (c = 1; c <= ncols; c++) {
                if (field_line[c-1] == '*') {
                    place_mine(r, c);
                }
            }
        }

        fno++;
        if (fno > 1) {
            printf("\n");
        }
        printf("Field #%d:\n", fno);
        print_field(nrows, ncols);
    }
    return 0;
}
