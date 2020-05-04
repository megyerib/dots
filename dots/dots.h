#ifndef DOTS_H
#define DOTS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define key_esc 27
#define key_up 72
#define key_left 75
#define key_down 80
#define key_right 77
#define key_enter 13

#define window_width 80
#define window_height 25

enum {
    CROSS = 1, H_LN, V_LN, SYMBOL
};

extern int
min_x,
max_x,
min_y,
max_y,
grid_x,
grid_y,
blue,
red,
first,
response;

#endif // DOTS_H
