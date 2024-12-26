#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define COLOR_BLACK 30
#define COLOR_RED 31
#define COLOR_GREEN 32
#define COLOR_YELLOW 33
#define COLOR_BLUE 34
#define COLOR_MAGENTA 35
#define COLOR_CYAN 36
#define COLOR_WHITE 37
#define BACKGROUND_COLOR_GREEN 2
#define BACKGROUND_COLOR_BLACK 0

/* Function to set text color and background color in the terminal */
void set_color(int fg, int bg) {
    printf("\033[%d;%dm", fg, bg + 40); /* fg is foreground color, bg is background color */
}

/* Function to reset text color and background color to default */
void reset_color() {
    printf("\033[0m");
}

/* Function to move the cursor to a specific position in the terminal */
void set_cursor_position(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

int main() {

    char tree[] = { 0xb0, 0xb1, 0xb2,  /* Tree characters */
                    0xf8, 0xf9, 0xfa,      /* Decoration characters */
                    0xfe                /* Light character */ };
    char t[1];
    int row, col; /* Row and column positions */
    int i, c;     /* Random index and color */

    srand(time(NULL));

    printf("\033[2J"); /* ANSI escape code to clear screen */

    /* Draw the tree trunk */

    set_color(COLOR_YELLOW, BACKGROUND_COLOR_BLACK);

    for (row = 20; row <= 23; row++) {
        set_cursor_position(row, 40 - 1);
        printf("%c%c%c",tree[0],tree[1],tree[2]);
    }

    /* Draw the tree leaves and decorations */

    for (row = 0; row < 20; row++) {
        set_cursor_position(1 + row, 40 - row);
        for (col = 40 - row; col <= 40 + row; col++) {
            i = rand() % 7;
            if (i < 3) { /* Tree characters (0, 1, 2) */
                c = ((rand() & 1) ? COLOR_BLACK : COLOR_GREEN);
                set_color(c, BACKGROUND_COLOR_GREEN);
            } else { /* Decorations and lights (3 to 6) */
                c = COLOR_RED + (rand() % 7); /* Randomly choose a bright color (red to white) */
                set_color(c, BACKGROUND_COLOR_GREEN);
            }
            printf("%c", tree[i]); /* Print the character */
        }
    }

    /* Draw the star at the top of the tree */

    set_color(COLOR_YELLOW, BACKGROUND_COLOR_GREEN);
    set_cursor_position(1, 40);
    printf("%c", '*');

    /* Print a festive message below the tree */

    reset_color(); /* Reset colors to default */
    set_cursor_position(25, 1); /* Position cursor for message */
    printf("Merry Christmas!\n"); /* Print the message */

    /*Detect key press and exit the program*/
    getchar();
    printf("\033[H\033[J");
    printf("See you next year!");

    return 0;
}
