#pragma once

void step(int x, int y);
void insert_char(int x, int y, char ch);
void drawgrid(int start_x, int start_y, int x, int y);
void draw_frame(int start_x, int start_y, int x, int y);
void draw_mark(int x, int y, int mark);
void hl_player(int player, int mode, char*blue_name, char*red_name);
void refresh_score(int player, int score);
void place_hor(int place);
void place_ver(int place);
void build_menu(void);
