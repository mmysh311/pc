#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STRLEN      12
#define MAX_ROWS    250
#define MAX_COLS    250
#define WHITE       'O'

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int height;
    int width;
    char name[STRLEN+1];
    char bitmap[MAX_ROWS][MAX_COLS];
} image_t;

bool
image_contains(
    image_t *pimg,
    int x,
    int y
)
{
    return 1 <= x && x <= pimg->width
        && 1 <= y && y <= pimg->height;
}

char
image_get_pixel(
    const image_t *pimg,
    int x,
    int y
)
{
    return pimg->bitmap[y-1][x-1];
}

void
image_set_pixel(
    image_t *pimg,
    int x,
    int y,
    char color
)
{
    pimg->bitmap[y-1][x-1] = color;
}

void
image_clear(
    image_t *pimg
)
{
    int x, y;

    for (y = 1; y <= pimg->height; y++)
        for (x = 1; x <= pimg->width; x++)
            image_set_pixel(pimg, x, y, WHITE);
}

void
image_create(
    image_t *pimg,
    int ncols,
    int nrows
)
{
    pimg->width  = ncols;
    pimg->height = nrows;
    image_clear(pimg);
}

void 
image_draw_vertical(
    image_t *pimg,
    int x1,
    int y1,
    int y2,
    char color
)
{
    int y;

    for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
        image_set_pixel(pimg, x1, y, color);
}

void 
image_draw_horizontal(
    image_t *pimg,
    int x1,
    int x2,
    int y1,
    char color
)
{
    int x;

    for (x = MIN(x1, x2); x <= MAX(x1, x2); x++)
        image_set_pixel(pimg, x, y1, color);
}

void 
image_draw_rectangle(
    image_t *pimg,
    int x1,
    int y1,
    int x2,
    int y2,
    char color
)
{
    int x, y;

    for (y = MIN(y1, y2); y <= MAX(y1, y2); y++)
        for (x = MIN(x1, x2); x <= MAX(x1, x2); x++)
            image_set_pixel(pimg, x, y, color);
}

#define DEQUE_CAP ((MAX_ROWS) * (MAX_COLS))

typedef struct {
    int x;
    int y;
} pair_t;

typedef struct {
    pair_t data[DEQUE_CAP];
    int head;
    int tail;
    int size;
} deque_t;

void
deque_init(
    deque_t *pdq
)
{
    pdq->head = 0;
    pdq->tail = 0;
    pdq->size = 0;
}

void
deque_pushback(
    deque_t *pdq,
    pair_t pi
)
{
    pdq->data[pdq->tail] = pi;
    pdq->tail = (pdq->tail + 1) % DEQUE_CAP;
    pdq->size++;
}

pair_t deque_popfront(
    deque_t *pdq
)
{
    pair_t pi = pdq->data[pdq->head];
    pdq->head = (pdq->head + 1) % DEQUE_CAP;
    pdq->size--;
    return pi;
}

bool 
deque_is_empty(
    const deque_t *pdq
)
{
    return pdq->size == 0;
}

void
image_fill_region(
    image_t *pimg,
    int x1,
    int y1,
    char color
)
{
    pair_t start;
    char old_color;
    deque_t q;
    bool visited[MAX_ROWS][MAX_COLS] = {0};

    start.x = x1;
    start.y = y1;
    old_color = image_get_pixel(pimg, start.x, start.y);

    deque_init(&q);
    deque_pushback(&q, start);
    visited[start.y-1][start.x-1] = true;

    while(!deque_is_empty(&q)) {
        int i;
        const int yoff[4] = { -1,  0,  1,  0 };
        const int xoff[4] = {  0,  1,  0, -1 };

        pair_t pi = deque_popfront(&q);
        image_set_pixel(pimg, pi.x, pi.y, color);

        for (i = 0; i < 4; i++) {
            pair_t near;

            near.x = pi.x + xoff[i];
            near.y = pi.y + yoff[i];

            if (image_contains(pimg, near.x, near.y) &&
                !visited[near.y-1][near.x-1] &&
                image_get_pixel(pimg, near.x, near.y) == old_color
            ) {
                visited[near.y-1][near.x-1] = true;
                deque_pushback(&q, near);
            }
        }
    }
}

void
image_write(
    image_t * pimg,
    const char * name
)
{
    int x, y;

    strcpy(pimg->name, name);

    puts(pimg->name);

    for (y = 1; y <= pimg->height; y++) {
        for (x = 1; x <= pimg->width; x++)
            putchar(image_get_pixel(pimg, x, y));
        putchar('\n');
    }
}

int
main()
{
    char cmd;
    image_t img = {0};

    bool done = false;
    while (!done && scanf(" %c", &cmd) != EOF) {
        int ncols, nrows;
        int x1, x2, y1, y2;
        char c;
        char name[STRLEN+1];

        switch (cmd) {
            case 'I':
                scanf("%d %d", &ncols, &nrows);
                image_create(&img, ncols, nrows);
                break;
            case 'C':
                image_clear(&img);
                break;
            case 'L':
                scanf("%d %d %c", &x1, &y1, &c);
                image_set_pixel(&img, x1, y1, c);
                break;
            case 'V':
                scanf("%d %d %d %c", &x1, &y1, &y2, &c);
                image_draw_vertical(&img, x1, y1, y2, c);
                break;
            case 'H':
                scanf("%d %d %d %c", &x1, &x2, &y1, &c);
                image_draw_horizontal(&img, x1, x2, y1, c);
                break;
            case 'K':
                scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
                image_draw_rectangle(&img, x1, y1, x2, y2, c);
                break;
            case 'F':
                scanf("%d %d %c", &x1, &y1, &c);
                image_fill_region(&img, x1, y1, c);
                break;
            case 'S':
                scanf(" %12s", name);
                image_write(&img, name);
                break;
            case 'X':
                done = true;
                break;
            default:
                break;
            }
    }
    return 0;
}
