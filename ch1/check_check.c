#include <stdio.h>
#include <stdbool.h>

#define N 8

char board[N][N];

bool
on_board(
    int x,
    int y
) {
    return 0 <= x && x < N &&
           0 <= y && y < N;
}

bool
jumping_attack(
    int kx,
    int ky,
    const int *op_dx,
    const int *op_dy,
    int n,
    char target
)
{
    int i;
    for (i = 0; i < n; i++) {
        int op_x = kx + op_dx[i];
        int op_y = ky + op_dy[i];

        if (on_board(op_x, op_y) && board[op_y][op_x] == target)
            return true;
    }
    return false;
}

bool
sliding_attack(
    int kx,
    int ky,
    const int *op_dx,
    const int *op_dy,
    int n,
    char target
)
{
    int i;
    for (i = 0; i < n; i++) {
        int op_x = kx;
        int op_y = ky;

        while(true) {
            op_x += op_dx[i];
            op_y += op_dy[i];

            if (!on_board(op_x, op_y))
                break;

            if (board[op_y][op_x] == target)
                return true;

            if (board[op_y][op_x] != '.')
                break;
        }
    }
    return false;
}

bool
king_in_check(
    int kx,
    int ky
)
{
    char king = board[ky][kx];

    char by_bishop = (king == 'K') ? 'b' : 'B';
    char by_knight = (king == 'K') ? 'n' : 'N';
    char by_queen  = (king == 'K') ? 'q' : 'Q';
    char by_rook   = (king == 'K') ? 'r' : 'R';
    char by_pawn   = (king == 'K') ? 'p' : 'P';

    int by_pawn_dy[2]   = {  1,  1 };
    int by_pawn_dx[2]   = { -1,  1 };

    int by_knight_dy[8] = { -2, -2, -1,  1,  2,  2,  1, -1 };
    int by_knight_dx[8] = { -1,  1,  2,  2,  1, -1, -2, -2 };

    int by_bishop_dy[4] = { -1, -1,  1,  1 };
    int by_bishop_dx[4] = { -1,  1,  1, -1 };

    int by_rook_dy[4]   = { -1,  0,  1,  0 };
    int by_rook_dx[4]   = {  0,  1,  0, -1 };

    int by_queen_dy[8]  = { -1, -1,  0,  1,  1,  1,  0, -1 };
    int by_queen_dx[8]  = {  0,  1,  1,  1,  0, -1, -1, -1 };

    by_pawn_dy[0] = by_pawn == 'P' ? 1 : -1;
    by_pawn_dy[1] = by_pawn == 'P' ? 1 : -1;

    return jumping_attack(kx, ky, by_pawn_dx,   by_pawn_dy,   2, by_pawn  ) ||
           jumping_attack(kx, ky, by_knight_dx, by_knight_dy, 8, by_knight) ||
           sliding_attack(kx, ky, by_bishop_dx, by_bishop_dy, 4, by_bishop) ||
           sliding_attack(kx, ky, by_rook_dx,   by_rook_dy,   4, by_rook  ) ||
           sliding_attack(kx, ky, by_queen_dx,  by_queen_dy,  8, by_queen );
}

int
main()
{
    int gno = 1;
    for (;;) {
        int x, y;
        int Kx, Ky, kx, ky;
        Kx = Ky = kx = ky = -1;

        for (y = 0; y < N; y++) {
            for(x = 0; x < N; x++) {
                char piece;
                scanf(" %c", &piece);

                switch (piece) {
                case 'K':
                    Kx = x;
                    Ky = y;
                    break;
                case 'k':
                    kx = x;
                    ky = y;
                    break;
                }
                board[y][x] = piece;
            }
        }

        if (kx == -1 && Kx == -1)
            break;

        printf("Game #%d: ", gno);
        if (king_in_check(Kx, Ky)) {
            puts("white king is in check.");
        } else if (king_in_check(kx, ky)) {
            puts("black king is in check.");
        } else {
            puts("no king is in check.");
        }

        gno++;
    }
    return 0;
}
