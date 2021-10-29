#pragma once

typedef enum dots_key_t {
	KEY_ESC = 0,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_ENTER,

	KEY_NUM
} dots_key_t; // key_t conflicts on Linux

typedef enum dots_color_t {
	COLOR_BLACK = 0,
	COLOR_WHITE,
	COLOR_RED,
	COLOR_BLUE,

	COLOR_NUM
} dots_color_t;

void init(void);

void clean(void);

dots_key_t get_key(void);

void wait_for_any_key(void);

void clear_screen(void);

int cursor_x(void);

int cursor_y(void);

void go_to(int x, int y);

void wait_ms(int ms);

void set_text_color(dots_color_t color);

void set_text_bg(dots_color_t color);
