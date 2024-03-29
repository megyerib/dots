#include "dots.h"
#include "econio.c"
#include "screen.c"
#include "settings.c"
#include "game.c"

// Globális változók
int min_x = 0;
int max_x = window_width - 1;
int min_y = 0;
int max_y = window_height - 1;

int grid_x = 3,
grid_y = 3,
blue = 1,
red = 2,
first = 1,
response = 4;

int main() {
    srand(time(NULL));
    int key, y = 13;

    build_menu();

    while (1) {
        key = push_arrow();
        if (key == key_up || key == key_down) {
            if (key == key_up) y--;
            if (key == key_down) y++;
            if (y < 13) y = 13;
            if (y > 15) y = 15;
            gotoxy(34, y);
        }
        else if (key == key_enter) {
            clrscr();
            switch (y) {
                case 13: // Start_game
                    game();
                    break;
                case 14: // Settings
                    settings();
                    break;
                case 15: // Quit
                    exit(0);
                    break;
            }
            build_menu();
            y = 13;
        }
    }

    return 0;
}
