#include "dots.h"
#include <string.h>

void step(int x, int y)
{
    if (x < min_x) {
        x = min_x;
    }
    if (x > max_x) {
        x = max_x;
    }
    if (y < min_y) {
        y = min_y;
    }
    if (y > max_y) {
        y = max_y;
    }
    go_to(x, y);
}

void insert_char(int x, int y, char ch)
{
    go_to(x, y);
    printf("%c", ch);
    go_to(cursor_x()-1, cursor_y());
}

void drawgrid(int start_x, int start_y, int x, int y)
{
    int i, j;
    for (i = 0; i <= x; ++i) {
        for (j = 0; j <= y; ++j) {
            insert_char(start_x+i*2,start_y+j*2,'+');
        }
    }
    min_x = start_x;
    max_x = start_x+x*2;
    min_y = start_y;
    max_y = start_y+y*2;
    step(0,0);
}

void draw_frame(int start_x, int start_y, int x, int y)
{
    int i;
    for (i = 1; i < x-1; ++i) { // Vízsz
        insert_char(start_x+i,start_y,205);
        insert_char(start_x+i,start_y+y-1,205);
    }
    for (i = 1; i < y-1; ++i) { // Függ
        insert_char(start_x,start_y+i,186);
        insert_char(start_x+x-1,start_y+i,186);
    }
    insert_char(start_x,start_y,201); //bf
    insert_char(start_x+x-1,start_y,187); //jf
    insert_char(start_x,start_y+y-1,200); //ba
    insert_char(start_x+x-1,start_y+y-1,188); //ja
    go_to(0,0);
}

void draw_mark(int x, int y, int mark)
{
    int color;
    char chr;
    if (mark == 1) { // Ember
        color = COLOR_BLUE;
        chr = 'O';
    } else if (mark == 2) { // Gép
        color = COLOR_RED;
        chr = 'X';
    }
    else {
        return;
    }

    set_text_color(color);
    insert_char(6+(36-grid_x)+2*y-1, 1+(11-grid_y)+2*x-1, chr);
    set_text_color(COLOR_WHITE);
}

void hl_player(int player, int mode, char*blue_name, char*red_name)
{
    int color, y;
    char name[5];
    // JÁTÉKOS
    if (player == 1) {
        color = COLOR_BLUE;
        strcpy(name, blue_name);
        y = 1;
    }
    else if (player == 2) {
        color = COLOR_RED;
        strcpy(name, red_name);
        y = 4;
    }
    else {
        return;
    }
    // Mód
    if (mode) { // 1-re kiemel, 0-ra visszaállít
        set_text_color(COLOR_BLACK);
        set_text_bg(color);
    }
    else {
        set_text_color(color);
        set_text_bg(COLOR_BLACK);
    }
    go_to(1, y);
    printf("%s", name);
    set_text_color(COLOR_WHITE);
    set_text_bg(COLOR_BLACK);
}

void refresh_score(int player, int score)
{
    int y;
    if (player == 1) {
        y = 2;
    }
    else if (player == 2) {
        y = 5;
    }
    else {
        return;
    }
    go_to(1, y);
    printf("%4d", score);
}

void place_hor(int place)
{
    int row = place/grid_x+1;
    int col = place%grid_x>0?place%grid_x:grid_x;
    if (col%grid_x == 0)
        row--;

    int start_x = 6+(73-(2*grid_x-1))/2-1;
    int start_y = 1+(23-(2*grid_y-1))/2-1;

    int x, y;

    x = start_x+col*2-1;
    y = start_y+(row-1)*2;

    insert_char(x, y, '-');
}

void place_ver(int place)
{
    int row = place/(grid_x+1)+1;
    int col = place%(grid_x+1)>0?place%(grid_x+1):(grid_x+1);
    if (col%(grid_x+1) == 0)
        row--;

    int start_x = 6+(73-(2*grid_x-1))/2-1;
    int start_y = 1+(23-(2*grid_y-1))/2-1;

    int x, y;

    x = start_x+(col-1)*2;
    y = start_y+(row)*2-1;

    insert_char(x, y, 179);
}

void build_menu(void)
{
    clear_screen();
    set_text_color(COLOR_WHITE);
    go_to(16,3);printf("`7MM\"\"\"Yb.  ");set_text_color(COLOR_BLUE);printf("   .g8\"\"8q. "); set_text_color(COLOR_WHITE);printf("  MMP\"\"MM\"\"YMM  .M\"\"\"bgd");
    go_to(16,4);printf("  MM    `Yb. ");  set_text_color(COLOR_BLUE); printf(".dP'    `YM.");  set_text_color(COLOR_WHITE);printf(" P'   MM   `7 ,MI    \"Y");
    go_to(16,5);printf("  MM     `Mb ");  set_text_color(COLOR_BLUE); printf("dM'      `MM  ");  set_text_color(COLOR_WHITE);printf("    MM      `MMb.");
    go_to(16,6);printf("  MM      MM ");  set_text_color(COLOR_BLUE); printf("MM        MM  ");  set_text_color(COLOR_WHITE);printf("    MM        `YMMNq.");
    go_to(16,7);printf("  MM     ,MP ");  set_text_color(COLOR_BLUE); printf("MM.      ,MP  ");  set_text_color(COLOR_WHITE);printf("    MM      .     `MM");
    go_to(16,8);printf("  MM    ,dP' ");  set_text_color(COLOR_BLUE); printf("`Mb.    ,dP'  ");  set_text_color(COLOR_WHITE);printf("    MM      Mb     dM");
    go_to(16,9);printf(".JMMmmmdP'   ");  set_text_color(COLOR_BLUE);printf("  `\"bmmd\"'  "); set_text_color(COLOR_WHITE);printf("    .JMML.    P\"Ybmmd\"");

    draw_frame(29,11,25,7);

    go_to(36,13); printf("Start game");
    go_to(36,14); printf("Settings");
    go_to(36,15); printf("Quit");

    go_to(34,13);
}
