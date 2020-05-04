#pragma once

int ver_size(void);
int hor_size(void);
int fields_size(void);
int start_x(void);
int start_y(void);
int waitforarrow(void);
int push_arrow(void);
int whatshere(int x, int y);
int check_square(int x, int y, int* v_ln, int* h_ln);
int covering(int y, int x, int* v_ln, int* h_ln);
void array_copy(int* dest, int* src, int cnt);
void place_random(int* ver_lines, int* hor_lines);
void complete(int y, int x, int* v_ln, int* h_ln);
int nocomplete(int* ver_lines, int* hor_lines);
int computer(int* ver_lines, int* hor_lines);
int human(int* ver_lines, int* hor_lines);
void game();
