#include "port.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static const int key_value[] = {
    [KEY_ESC]   = 27,
    [KEY_UP]    = 72,
    [KEY_LEFT]  = 75,
    [KEY_DOWN]  = 80,
    [KEY_RIGHT] = 77,
    [KEY_ENTER] = 13
};

static const int color_value[] = {
    [COLOR_BLACK] = 0,
    [COLOR_WHITE] = 0,
    [COLOR_RED]   = 0,
    [COLOR_BLUE]  = 0
};

void init(void)
{
    srand((unsigned int)time(NULL));
}

void clean(void)
{

}

dots_key_t get_key(void)
{
    (void) key_value;
    
    char key_val;
    fread(&key_val, 1, 1, stdin);
    return (int)key_val;
}

void wait_for_any_key(void)
{

}

void clear_screen(void)
{

}

int cursor_x(void)
{
    return 0;
}

int cursor_y(void)
{
    return 0;
}

void go_to(int x, int y)
{
    (void) x;
    (void) y;
}

void wait_ms(int ms)
{
    (void) ms;
}

void set_text_color(dots_color_t color)
{
    (void) color;
}

void set_text_bg(dots_color_t color)
{
    (void) color;
    (void) color_value;
}

/* put terminal in raw mode - see termio(7I) for modes */
static void tty_raw(void)
{
    struct termios raw;

    raw = orig_termios;  /* copy original and then modify below */

    /* input modes - clear indicated ones giving: no break, no CR to NL, 
       no parity check, no strip char, no start/stop output (sic) control */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    /* output modes - clear giving: no post processing such as NL to CR+NL */
    raw.c_oflag &= ~(OPOST);

    /* control modes - set 8 bit chars */
    raw.c_cflag |= (CS8);

    /* local modes - clear giving: echoing off, canonical off (no erase with 
       backspace, ^U,...),  no extended functions, no signal chars (^Z,^C) */
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    /* control chars - set return condition: min number of bytes and timer */
    raw.c_cc[VMIN] = 5; raw.c_cc[VTIME] = 8; /* after 5 bytes or .8 seconds
                                                after first byte seen      */
    raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 0; /* immediate - anything       */
    raw.c_cc[VMIN] = 2; raw.c_cc[VTIME] = 0; /* after two bytes, no timer  */
    raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 8; /* after a byte or .8 seconds */

    /* put terminal in raw mode after flushing */
    if (tcsetattr(ttyfd,TCSAFLUSH,&raw) < 0) {
        fatal("can't set raw mode");
    }
}