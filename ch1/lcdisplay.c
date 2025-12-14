#include <stdio.h>
#include <string.h>

#define NROWS   5
#define BUFLEN  120
#define STRLEN  9

typedef enum {
    SEG_BLANK,      /* "   " */
    SEG_BOTH,       /* "| |" */
    SEG_DASH,       /* " - " */
    SEG_LEFT,       /* "|  " */
    SEG_RIGHT       /* "  |" */
} seg_t;

const seg_t patterns[10][NROWS] = {
    {
        SEG_DASH,   /* " - " */
        SEG_BOTH,   /* "| |" */
        SEG_BLANK,  /* "   " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH    /* " - " */
    },
    {
        SEG_BLANK,  /* "  " */
        SEG_RIGHT,  /* " |" */
        SEG_BLANK,  /* "  " */
        SEG_RIGHT,  /* " |" */
        SEG_BLANK   /* "  " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_DASH,   /* " - " */
        SEG_LEFT,   /* "|  " */
        SEG_DASH    /* " - " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_DASH    /* " - " */
    },
    {
        SEG_BLANK,  /* "   " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_BLANK   /* "   " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_LEFT,   /* "|  " */
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_DASH    /* " - " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_LEFT,   /* "|  " */
        SEG_DASH,   /* " - " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH    /* " - " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_BLANK,  /* "   " */
        SEG_RIGHT,  /* "  |" */
        SEG_BLANK   /* "   " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH,   /* " - " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH    /* " - " */
    },
    {
        SEG_DASH,   /* " - " */
        SEG_BOTH,   /* "| |" */
        SEG_DASH,   /* " - " */
        SEG_RIGHT,  /* "  |" */
        SEG_DASH    /* " - " */
    }
};

void
buf_append(
    char *buf,
    int  *pos,
    seg_t ptn,
    int   scale
)
{
    int i;

    switch (ptn) {
    case SEG_BLANK:
        for (i = 0; i < scale + 2; i++)
            buf[(*pos)++] = ' ';
        break;
    case SEG_BOTH:
        buf[(*pos)++] = '|';
        for (i = 0; i < scale; i++)
            buf[(*pos)++] = ' ';
        buf[(*pos)++] = '|';
        break;
    case SEG_DASH:
        buf[(*pos)++] = ' ';
        for (i = 0; i < scale; i++)
            buf[(*pos)++] = '-';
        buf[(*pos)++] = ' ';
        break;
    case SEG_LEFT:
        buf[(*pos)++] = '|';
        for (i = 0; i < scale + 1; i++)
            buf[(*pos)++] = ' ';
        break;
    case SEG_RIGHT:
        for (i = 0; i < scale + 1; i++)
            buf[(*pos)++] = ' ';
        buf[(*pos)++] = '|';
        break;
    }
}

int
main()
{
    int scale;
    char numstr[STRLEN];


    while (scanf("%d %8s", &scale, numstr) != EOF) {
        int len;
        int row, j;

        if (scale == 0 && strcmp(numstr, "0") == 0)
            break;

        len = strlen(numstr);
        for (row = 0; row < NROWS; row++) {
            char buf[BUFLEN];
            int pos = 0;
            int rep;

            for (j = 0; j < len; j++) {
                int digit = numstr[j] - '0';
                buf_append(buf, &pos, patterns[digit][row], scale);
                buf[pos++] = ' ';
            }
            buf[pos - 1] = '\0';

            rep = (row == 1 || row == 3) ? scale : 1;
            while (rep-- > 0)
                puts(buf);
        }
        putchar('\n');
    }
    return 0;
}
