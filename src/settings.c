#include "dots.h"
#include "port.h"

void bar(int min, int max, int val) {
    int i;
    for (i = min; i <= max; ++i) {
        if (i <= val)
            putchar(219);
        else
            putchar(177);
    }
}

void choose(char* option1, char* option2, int chosen) {
    if (chosen == 1)
        printf("[%s]  %s ", option1, option2);
    else if (chosen == 2)
        printf(" %s  [%s]", option1, option2);
}

void set_globals_valid(void) {
    if (grid_x > 36)  grid_x = 36;
    if (grid_x < 3)   grid_x = 3;
    if (grid_y > 11)  grid_y = 11;
    if (grid_y < 3)   grid_y = 3;
    if (blue > 2)     blue = 2;
    if (blue < 1)     blue = 1;
    if (red > 2)      red = 2;
    if (red < 1)      red = 1;
    if (first > 2)    first = 2;
    if (first < 1)    first = 1;
    if (response > 9) response = 9;
    if (response < 0) response = 0;
}

void load_game_settings(void) {
    FILE*set;
    set = fopen("settings.dat", "r");

    if (set) {
        fread(&grid_x, sizeof(int), 1, set);
        fread(&grid_y, sizeof(int), 1, set);
        fread(&blue, sizeof(int), 1, set);
        fread(&red, sizeof(int), 1, set);
        fread(&first, sizeof(int), 1, set);
        fread(&response, sizeof(int), 1, set);
    }
    fclose(set);
    set_globals_valid();
}

void save_settings(void) {
    set_globals_valid();
    FILE*set;
    set = fopen("settings.dat", "w");
    fwrite(&grid_x, sizeof(int), 1, set);
    fwrite(&grid_y, sizeof(int), 1, set);
    fwrite(&blue, sizeof(int), 1, set);
    fwrite(&red, sizeof(int), 1, set);
    fwrite(&first, sizeof(int), 1, set);
    fwrite(&response, sizeof(int), 1, set);
    fclose(set);
}

void settings(void) {
    int row = 1, save = 0;
    dots_key_t key;

    load_game_settings();

    draw_frame(0,0,window_width,window_height);
    go_to(2,0);
    printf("SETTINGS");

    // Elsõ width
    go_to(6,4);
    printf("   Width %2d ", grid_x);
    bar(3, 36, grid_x);

    // Elsõ height
    go_to(6,6);
    printf("  Height %2d ", grid_y);
    bar(3, 11, grid_y);

    // Elsõ blue
    go_to(6,8);
    set_text_color(COLOR_BLUE);
    printf("Blue (O)    ");
    set_text_color(COLOR_WHITE);
    choose("Human", "Computer", blue);

    // Elsõ red
    go_to(6,10);
    set_text_color(COLOR_RED);
    printf(" Red (X)    ");
    set_text_color(COLOR_WHITE);
    choose("Human", "Computer", red);

    // Elsõ first
    go_to(6,12);
    printf("   First    ");
    choose("Blue", "Red", first);

    // Elsõ response
    go_to(6,14);
    printf("Response .%d ", response);
    bar(0, 9, response);

    // Save
    go_to(6,16);
    printf("SAVE");

    while (1) {
        if (row < 1)
            row = 1;
        if (row > 7)
            row = 7;

        if (row == 1) { // grid_x
            go_to(4, 4);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        grid_x++;
                        break;
                    case KEY_LEFT:
                        grid_x--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 1) {
                    break;
                }

                set_globals_valid();

                go_to(15,4);
                printf("%2d", grid_x);
                go_to(18,4);
                bar(3, 36, grid_x);
                go_to(4,4);
            }
        }
        else if (row == 2) { // grid_y
            go_to(4, 6);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        grid_y++;
                        break;
                    case KEY_LEFT:
                        grid_y--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 2) {
                    break;
                }

                set_globals_valid();

                go_to(15,6);
                printf("%2d", grid_y);
                go_to(18,6);
                bar(3, 11, grid_y);
                go_to(4,6);
            }
        }
        else if (row == 3) { // BLUE
            go_to(4, 8);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        blue++;
                        break;
                    case KEY_LEFT:
                        blue--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 3) {
                    break;
                }

                set_globals_valid();

                go_to(15,8);
                printf("  ");
                go_to(18,8);
                choose("Human", "Computer", blue);
                go_to(4,8);
            }
        }
        else if (row == 4) { // RED
            go_to(4, 10);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        red++;
                        break;
                    case KEY_LEFT:
                        red--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 4) {
                    break;
                }

                set_globals_valid();

                go_to(15,10);
                printf("  ");
                go_to(18,10);
                choose("Human", "Computer", red);
                go_to(4,10);
            }
        }
        else if (row == 5) { // FIRST
            go_to(4, 12);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        first++;
                        break;
                    case KEY_LEFT:
                        first--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 5) {
                    break;
                }

                set_globals_valid();

                go_to(15,12);
                printf("  ");
                go_to(18,12);
                choose("Blue", "Red", first);
                go_to(4,12);
            }
        }
        else if (row == 6) { // RESPONSE
            go_to(4, 14);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_RIGHT:
                        response++;
                        break;
                    case KEY_LEFT:
                        response--;
                        break;
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 6) {
                    break;
                }


                set_globals_valid();

                go_to(15,14);
                printf(".%d", response);
                go_to(18,14);
                bar(0, 9, response);
                go_to(4,14);
            }
        }
        else if (row == 7) { // SAVE
            go_to(4, 16);
            while(1) {
                key = get_key();
                switch (key) {
                    case KEY_UP:
                        row--;
                        break;
                    case KEY_DOWN:
                        row++;
                        break;
                    case KEY_ENTER:
                        save = 1;
                        break;
                    default:
                        continue;
                }
                if (row != 7) {
                    break;
                }

                if (save) {
                    save_settings();
                    return;
                }

                go_to(4,16);
            }
        }
    }
}
