#include "port.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include "econio.h"
#include <time.h>
#include <conio.h>

static const int windows_key_value[KEY_NUM] = {
    [KEY_ESC]   = 27,
    [KEY_UP]    = 72,
    [KEY_LEFT]  = 75,
    [KEY_DOWN]  = 80,
    [KEY_RIGHT] = 77,
    [KEY_ENTER] = 13
};

static const int econio_color_value[COLOR_NUM] = {
    [COLOR_BLACK] = BLACK,
    [COLOR_WHITE] = WHITE,
    [COLOR_RED]   = LIGHTRED,
    [COLOR_BLUE]  = LIGHTBLUE
};

void init_random(void)
{
	srand((unsigned int)time(NULL));
}

dots_key_t get_key(void)
{
    int key_val = 0;

    while(true) {
        key_val = getch();

        if(key_val != 224) {
            if(key_val == windows_key_value[KEY_ENTER]) {
                return KEY_ENTER;
            }
            continue;
        }

        key_val = getch();

        for(int i = 0; i < KEY_NUM; i++) {
            if (windows_key_value[i] == key_val) {
                return (dots_key_t)i;
            }
        }
    }
}

void wait_for_any_key(void)
{
    getch();
}

void clear_screen(void)
{
    clrscr();
}

int cursor_x(void)
{
    return wherex();
}

int cursor_y(void)
{
    return wherey();
}

void go_to(int x, int y)
{
    gotoxy(x, y);
}

void wait_ms(int ms)
{
    Sleep(ms);
}

void set_text_color(dots_color_t color)
{
    textcolor(econio_color_value[color]);
}

void set_text_bg(dots_color_t color)
{
    textbackground(econio_color_value[color]);
}
