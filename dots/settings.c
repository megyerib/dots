#include "dots.h"

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
    int i = 1;
    FILE*set;
    set = fopen("settings.dat", "r");
    int buf;
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
    int arrow, row = 1, save = 0;

    load_game_settings();

    draw_frame(0,0,window_width,window_height);
    gotoxy(2,0);
    printf("SETTINGS");

    // Elsõ width
    gotoxy(6,4);
    printf("   Width %2d ", grid_x);
    bar(3, 36, grid_x);

    // Elsõ height
    gotoxy(6,6);
    printf("  Height %2d ", grid_y);
    bar(3, 11, grid_y);

    // Elsõ blue
    gotoxy(6,8);
    textcolor(LIGHTBLUE);
    printf("Blue (O)    ");
    textcolor(WHITE);
    choose("Human", "Computer", blue);

    // Elsõ red
    gotoxy(6,10);
    textcolor(LIGHTRED);
    printf(" Red (X)    ");
    textcolor(WHITE);
    choose("Human", "Computer", red);

    // Elsõ first
    gotoxy(6,12);
    printf("   First    ");
    choose("Blue", "Red", first);

    // Elsõ response
    gotoxy(6,14);
    printf("Response .%d ", response);
    bar(0, 9, response);

    // Save
    gotoxy(6,16);
    printf("SAVE");

    while (1) {
        if (row < 1)
            row = 1;
        if (row > 7)
            row = 7;

        if (row == 1) { // grid_x
            gotoxy(4, 4);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        grid_x++;
                        break;
                    case key_left:
                        grid_x--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 1) {
                    break;
                }

                set_globals_valid();

                gotoxy(15,4);
                printf("%2d", grid_x);
                gotoxy(18,4);
                bar(3, 36, grid_x);
                gotoxy(4,4);
            }
        }
        else if (row == 2) { // grid_y
            gotoxy(4, 6);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        grid_y++;
                        break;
                    case key_left:
                        grid_y--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 2) {
                    break;
                }

                set_globals_valid();

                gotoxy(15,6);
                printf("%2d", grid_y);
                gotoxy(18,6);
                bar(3, 11, grid_y);
                gotoxy(4,6);
            }
        }
        else if (row == 3) { // BLUE
            gotoxy(4, 8);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        blue++;
                        break;
                    case key_left:
                        blue--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 3) {
                    break;
                }

                set_globals_valid();

                gotoxy(15,8);
                printf("  ");
                gotoxy(18,8);
                choose("Human", "Computer", blue);
                gotoxy(4,8);
            }
        }
        else if (row == 4) { // RED
            gotoxy(4, 10);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        red++;
                        break;
                    case key_left:
                        red--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 4) {
                    break;
                }

                set_globals_valid();

                gotoxy(15,10);
                printf("  ");
                gotoxy(18,10);
                choose("Human", "Computer", red);
                gotoxy(4,10);
            }
        }
        else if (row == 5) { // FIRST
            gotoxy(4, 12);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        first++;
                        break;
                    case key_left:
                        first--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 5) {
                    break;
                }

                set_globals_valid();

                gotoxy(15,12);
                printf("  ");
                gotoxy(18,12);
                choose("Blue", "Red", first);
                gotoxy(4,12);
            }
        }
        else if (row == 6) { // RESPONSE
            gotoxy(4, 14);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_right:
                        response++;
                        break;
                    case key_left:
                        response--;
                        break;
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    default:
                        continue;
                }
                if (row != 6) {
                    break;
                }


                set_globals_valid();

                gotoxy(15,14);
                printf(".%d", response);
                gotoxy(18,14);
                bar(0, 9, response);
                gotoxy(4,14);
            }
        }
        else if (row == 7) { // SAVE
            gotoxy(4, 16);
            while(1) {
                arrow = push_arrow();
                switch (arrow) {
                    case key_up:
                        row--;
                        break;
                    case key_down:
                        row++;
                        break;
                    case key_enter:
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

                gotoxy(4,16);
            }
        }
    }
}
