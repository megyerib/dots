#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

#include "econio.h"
#include "game.h"
#include "screen.h"
#include "settings.h"
#include "keys.h"

#define window_width  80
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
