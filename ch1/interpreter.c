#include <stdio.h>
#include <stdbool.h>

#define NREGS   10
#define NWORDS  1000
#define WORD_W  3
#define BUFLEN  5
#define MOD     1000

int buf_to_num(int buf[], int w) {
    int num = 0;

    int i;
    for (i = 0; i < w; i++)
        num = num * 10 + buf[i];

    return num;
}

void num_to_buf(int num, int buf[], int w) {
    while (w-- > 0) {
        buf[w] = num % 10;
        num /= 10;
    }
}

int
main()
{
    int ncases;
    scanf("%d", &ncases);
    getchar();
    getchar();

    while (ncases-- > 0) {
        int reg[NREGS] = {0};
        int ram[NWORDS][WORD_W] = {0};
        char buf[BUFLEN];
        int i, j;
        bool halt;

        i = 0;
        while(fgets(buf, sizeof(buf), stdin)) {
            int j;

            if (buf[0] == '\n')
                break;

            for (j = 0; j < WORD_W; j++)
                ram[i][j] = buf[j] - '0';

            i++;
            if (i == NWORDS)
                break;
        }

        i = j = 0;
        halt = false;
        while (!halt && 0 <= i && i < NWORDS) {
            int op = ram[i][0];
            int d = ram[i][1];
            int s = ram[i][2];

            switch (op) {
                case 1:
                    halt = true;
                    break;
                case 2:
                    reg[d] = s;
                    break;
                case 3:
                    reg[d] = (reg[d] + s) % MOD;
                    break;
                case 4:
                    reg[d] = (reg[d] * s) % MOD;
                    break;
                case 5:
                    reg[d] = reg[s];
                    break;
                case 6:
                    reg[d] = (reg[d] + reg[s]) % MOD;
                    break;
                case 7:
                    reg[d] = (reg[d] * reg[s]) % MOD;
                    break;
                case 8:
                    reg[d] = buf_to_num(ram[reg[s]], WORD_W);
                    break;
                case 9:
                    num_to_buf(reg[d], ram[reg[s]], WORD_W);
                    break;
                case 0:
                    if (reg[s] != 0)
                        i = reg[d] - 1;
                    break;
            }
            i++;
            j++;
        }
        printf("%d\n", j);
        if (ncases > 0)
            putchar('\n');
    }
    return 0;
}
