#include "port.h"

static const int key_value[KEY_NUM] = {
    [KEY_ESC]   = 27,
    [KEY_UP]    = 72,
    [KEY_LEFT]  = 75,
    [KEY_DOWN]  = 80,
    [KEY_RIGHT] = 77,
    [KEY_ENTER] = 13
};

static const int color_value[COLOR_NUM] = {
    [COLOR_BLACK] = BLACK,
    [COLOR_WHITE] = WHITE,
    [COLOR_RED]   = LIGHTRED,
    [COLOR_BLUE]  = LIGHTBLUE
};

void init_random(void)
{

}

dots_key_t get_key(void)
{

}

void wait_for_any_key(void)
{

}

void clear_screen(void)
{

}

int cursor_x(void)
{

}

int cursor_y(void)
{

}

void go_to(int x, int y)
{

}

void wait_ms(int ms)
{

}

void set_text_color(dots_color_t color)
{

}

void set_text_bg(dots_color_t color)
{

}
