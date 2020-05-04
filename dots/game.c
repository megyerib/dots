#include "dots.h"

int ver_size(void)    {return grid_y*(grid_x+1)+1;}
int hor_size(void)    {return (grid_y+1)*grid_x+1;}
int fields_size(void) {return grid_y*grid_x+1;}

int start_x(void) {return 6+(73-(2*grid_x-1))/2-1;}
int start_y(void) {return 1+(23-(2*grid_y-1))/2-1;}

int waitforarrow(void) {
    int keypress = 0, cnt = 0, i, j;
    while (1) {
            keypress = getch();
            if (keypress != 224) {
                if (keypress == key_enter) {
                    return 1;
                }
                if (keypress == key_esc) {
                    return 2;
                }
                if (keypress == 'c') {
                    return 3;
                }
                continue;
            }
            keypress = getch();
            switch (keypress) {
                case key_down:
                    step(wherex(), wherey()+1);
                    break;
                case key_up:
                    step(wherex(), wherey()-1);
                    break;
                case key_left:
                    step(wherex()-1, wherey());
                    break;
                case key_right:
                    step(wherex()+1, wherey());
                    break;
                default: cnt = 1;
            }
    }
}

int push_arrow(void) {
    int keypress = 0, cnt = 0, i, j;
    while (1) {
            keypress = getch();
            if (keypress != 224) {
                if (keypress == key_enter) {
                    return key_enter;
                }
                continue;
            }
            keypress = getch();
            return keypress;
    }
}

int whatshere(int x, int y) {
    int x_pty = grid_x%2?x%2:(x+1)%2;
    int y_pty = grid_y%2?y%2:(y+1)%2;

    if (x_pty && y_pty) { // 1 ptl ptl
        return CROSS;
    }
    else if (!x_pty && y_pty) { // 2 ps ptl
        return H_LN;
    }
    else if (x_pty && !y_pty) { // 3 ptl ps
        return V_LN;
    }
    else if (!x_pty && !y_pty) { // 4 ps ps
        return SYMBOL;
    }
    return 0;
}

int check_square(int x, int y, int* v_ln, int* h_ln) {
    if (
        h_ln[grid_x*(y-1)+x] &&
        h_ln[grid_x*(y)+x] &&
        v_ln[(grid_x+1)*(y-1)+x] &&
        v_ln[(grid_x+1)*(y-1)+x+1]
    ) {
        return 1;
    }
    return 0;
}

int covering(int y, int x, int* v_ln, int* h_ln) {
    return
        h_ln[grid_x*(x-1)+y]+
        h_ln[grid_x*(x)+y]+
        v_ln[(grid_x+1)*(x-1)+y]+
        v_ln[(grid_x+1)*(x-1)+y+1];
}

void array_copy(int* dest, int* src, int cnt) {
    int i;
    for (i = 0; i < cnt; ++i) {
        dest[i] = src[i];
    }
}

void place_random(int* ver_lines, int* hor_lines) {
    int i, j;
    int vers = grid_y*(grid_x+1);
    int empty_vers = 0;
    for (i = 1; i <= vers; ++i) {
        if (ver_lines[i] == 0)
            empty_vers++;
    }
    int hors = (grid_y+1)*grid_x;
    int empty_hors = 0;
    for (i = 1; i <= hors; ++i) {
        if (hor_lines[i] == 0)
            empty_hors++;
    }
    int sum = empty_vers + empty_hors;
    int r, place = 0;
    int x, y, x1, y1; // f: hanyadik sorban (a táblán) van a karakter

    int start_x = 6+(73-(2*grid_x-1))/2-1;
    int start_y = 1+(23-(2*grid_y-1))/2-1;

        r = sum>1?(rand()%sum)+1:1;
        if (r <= empty_vers) {
            j = 0;
            for (i = 1; j < r; ++i) {
                if (ver_lines[i] == 0)
                    j++;
            }
            ver_lines[i-1] = 1;
            place_ver(i-1);
        }
        else {
            j = 0;
            for (i = 1; j < (r-empty_vers); ++i) {
                if (hor_lines[i] == 0)
                    j++;
            }
            hor_lines[i-1] = 1;
            place_hor(i-1);
        }
}

void complete(int y, int x, int* v_ln, int* h_ln) {
    if (h_ln[grid_x*(x-1)+y] == 0) {
        h_ln[grid_x*(x-1)+y] = 1;
        place_hor(grid_x*(x-1)+y);
        return;
    }
    else if (h_ln[grid_x*(x)+y] == 0) {
        h_ln[grid_x*(x)+y] = 1;
        place_hor(grid_x*(x)+y);
        return;
    }
    else if (v_ln[(grid_x+1)*(x-1)+y] == 0) {
        v_ln[(grid_x+1)*(x-1)+y] = 1;
        place_ver((grid_x+1)*(x-1)+y);
        return;
    }
    else if (v_ln[(grid_x+1)*(x-1)+y+1] == 0) {
        v_ln[(grid_x+1)*(x-1)+y+1] = 1;
        place_ver((grid_x+1)*(x-1)+y+1);
        return;
    }
}

int nocomplete(int* ver_lines, int* hor_lines) {
    int *tmp_ver, *tmp_hor, *good_ver, *good_hor;
    int cnt_ver = 0, cnt_hor = 0;
    tmp_ver = malloc(ver_size()*sizeof(int));
    tmp_hor = malloc(hor_size()*sizeof(int));
    good_ver = malloc(ver_size()*sizeof(int));
    good_hor = malloc(hor_size()*sizeof(int));
    int i, j, k, ok = 0;

    //good_hor[0] = 0;
    //good_ver[0] = 0;

    array_copy(tmp_ver, ver_lines, ver_size());
    array_copy(tmp_hor, hor_lines, hor_size());

    // Függőlegesek ellenőrzése
    for (i = 1; i < ver_size(); ++i) {
        ok = 1;
        if (tmp_ver[i] == 1)
            continue;
        array_copy(tmp_ver, ver_lines, ver_size()); // Nulláz
        tmp_ver[i] = 1;
        for (j = 1; j < fields_size(); ++j) {
            if (covering(j%grid_x>0?j%grid_x:grid_x,j%grid_x>0?j/grid_x+1:j/grid_x,tmp_ver, tmp_hor) == 3) {
                ok = 0;
                break;
            }
        }
        // Ha nem csinált rossz négyzetet
        if (ok == 1) {
            good_ver[cnt_ver] = i;
            ++cnt_ver;
        }
    }

    array_copy(tmp_ver, ver_lines, ver_size()); // Visszaállít
    for (i = 1; i < hor_size(); ++i) {
        ok = 1;
        if (tmp_hor[i] == 1)
            continue;
        array_copy(tmp_hor, hor_lines, hor_size()); // Nulláz
        tmp_hor[i] = 1;
        for (j = 1; j < fields_size(); ++j) {
            if (covering(j%grid_x>0?j%grid_x:grid_x,j%grid_x>0?j/grid_x+1:j/grid_x,tmp_ver, tmp_hor) == 3) {
                ok = 0;
                break;
            }
        }

        // Ha nem csinált rossz négyzetet
        if (ok == 1) {
            good_hor[cnt_hor] = i;
            ++cnt_hor;
        }
    }

    int sum = cnt_hor+cnt_ver-1;
    if (sum >= 0) {
        int r = (rand()%(sum+1));
        if (r < cnt_ver) {
            ver_lines[good_ver[r]] = 1;
            place_ver(good_ver[r]);
        }
        else {
            hor_lines[good_hor[r-cnt_ver]] = 1;
            place_hor(good_hor[r-cnt_ver]);
        }
    }

    // FREE
    free(tmp_ver);
    free(tmp_hor);
    free(good_ver);
    free(good_hor);

    if (sum >= 0)
        return 1;
    return 0;
}

int computer(int* ver_lines, int* hor_lines) {
    int i, j;

    Sleep(response*100);
    // Befejezhető mezők befejezése
    for (j = 1; j <= grid_y; ++j) {
        for (i = 1; i <= grid_x; ++i) {
            if (covering(i, j, ver_lines, hor_lines) == 3) {
                complete(i, j, ver_lines, hor_lines);
                return 1;
            }
        }
    }

    if (nocomplete(ver_lines, hor_lines) == 0)
        place_random(ver_lines, hor_lines);
    return 1;
}

int human(int* ver_lines, int* hor_lines) {
    int wait = waitforarrow(), x1, y1, i, j;
    if (wait == 1) {  // Enter
        if (whatshere(wherex(), wherey()) == H_LN) {
            insert_char(wherex(), wherey(), '-');
            // Tömbhöz ad
            x1 = (wherex()-start_x()+1)/2;
            y1 = (wherey()-start_y())/2;
            if (!hor_lines[y1*grid_x+x1]) {
                hor_lines[y1*grid_x+x1] = 1;
            }
            else {
                return 0;
            }
        }
        else if (whatshere(wherex(), wherey()) == V_LN) {
            insert_char(wherex(), wherey(), 179);
            // Tömbhöz ad
            x1 = (wherex()-start_x())/2+1;
            y1 = (wherey()-start_y())/2;
            if (!ver_lines[y1*(grid_x+1)+x1]) {
                ver_lines[y1*(grid_x+1)+x1] = 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else if (wait == 2) {
        return -1; // Exit
    }
    else if (wait == 3) {
        computer(ver_lines, hor_lines); // Exit
    }
    return 1;
}

void game() {
    int x1, y1, i, j, winner = 0, winner_score;
    int player, player_change; // 1:ember, 2:gép first: beáll. kezdő játékos
    char blue_name[5] = "PLYR";
    char red_name[5] = "CPTR";
    char winner_name[20];

    load_game_settings();


    if (blue == 1) strcpy(blue_name, "PLYR");
    else strcpy(blue_name, "CPTR");
    if (red == 1) strcpy(red_name, "PLYR");
    else strcpy(red_name, "CPTR");

    draw_frame(0, 0, window_width, window_height);
    for (i = 1; i < 24; ++i) // Függőleges vonal
        insert_char(5,i,186);
    insert_char(5,0,203);
    insert_char(5,24,202);

    drawgrid(6+(36-grid_x), 1+(11-grid_y), grid_x, grid_y);

    gotoxy(1,1); textcolor(LIGHTBLUE); printf(blue_name);
    gotoxy(1,4); textcolor(LIGHTRED);  printf(red_name);
    textcolor(WHITE);
    refresh_score(1,0);
    refresh_score(2,0);

    int* hor_lines;
    int* ver_lines;
    int* fields;
    hor_lines = (int*)malloc(((grid_y+1)*grid_x+1)*sizeof(int));
    ver_lines = (int*)malloc((grid_y*(grid_x+1)+1)*sizeof(int));
    fields = (int*)malloc((grid_y*grid_x+1)*sizeof(int));

    int score[3] = {0};

    // Feltöltés nullákkal
    for (i = 0; i <= (grid_y+1)*grid_x; ++i)
        hor_lines[i] = 0;
    for (i = 0; i <= grid_y*(grid_x+1); ++i)
        ver_lines[i] = 0;
    for (i = 0; i <= grid_y*grid_x+1; ++i)
        fields[i] = 0;

    // Kezdésnél kiemeli a kezdőt
    player = first;
    hl_player(player, 1, blue_name, red_name);
    step(0,0);

    // GÉM
    while (score[1]+score[2]<grid_x*grid_y) {
        if (player == 1) { // Játékos
            if (blue == 1)
                player_change = human(ver_lines, hor_lines);
            else
                player_change = computer(ver_lines, hor_lines);
        } // Játékos vége
        else if (player == 2) { // Gép
            if (red == 1)
                player_change = human(ver_lines, hor_lines);
            else
                player_change = computer(ver_lines, hor_lines);
        }
            // Befejeződött a lépés
            if (player_change == -1) {
                free(hor_lines);
                free(ver_lines);
                free(fields);
                return; // Exit
            }

            for (i = 1; i <= grid_y; ++i) {
                for (j = 1; j <= grid_x; ++j) {
                    if (check_square(j,i,ver_lines,hor_lines) && fields[(i-1)*grid_x+j] == 0) {
                        x1 = wherex();
                        y1 = wherey();
                        draw_mark(i,j,player);
                        gotoxy(x1, y1);
                        fields[(i-1)*grid_x+j] = player;
                        score[player]++;
                        refresh_score(player, score[player]);
                        gotoxy(x1, y1);
                        player_change = 0;
                    }
                }
            }
            if (player_change) {
                x1 = wherex();
                y1 = wherey();
                hl_player(player, 0, blue_name, red_name);
                player = player==1?2:1;
                hl_player(player, 1, blue_name, red_name);
                gotoxy(x1, y1);
            }
    }

    // Vége a játéknak
    free(hor_lines);
    free(ver_lines);
    free(fields);

    draw_frame(35,1,15,3);
    gotoxy(36,2);
    if (score[1] > score[2]) {
        textcolor(LIGHTBLUE);
        printf("  Blue won!  ");
        textcolor(WHITE);
        if (blue == 1) winner = 1;
    }
    else if (score[1] < score[2]) {
        textcolor(LIGHTRED);
        printf("   Red won!  ");
        textcolor(WHITE);
        if (red == 1) winner = 2;
    }
    else {
        printf("    Draw!    ");
    }

    gotoxy(57, 23);
    printf("Press any key to exit");
    gotoxy(window_width-2, window_height-2);
    getch();
    return;
}
