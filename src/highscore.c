#include "dots.h"
#include <string.h>

typedef struct scr{
    char name[20];
    int score;
} SCORE;

void bubble_sort(SCORE** arr, int n) {
    int max = n-1, swap = 1, x;
    SCORE* tmp;
    while (swap && max > 0) {
        for (swap = 0, x = 0; x < max; ++x)
            if (arr[x]->score < arr[x+1]->score) {
                tmp = arr[x];
                arr[x] = arr[x+1];
                arr[x+1] = tmp;
                swap = 1;
            }
        max--;
    }
}

void fill_blank_highscore(void) {
    FILE*highscore;
    highscore = fopen("highscore.dat", "w");

    int i;
    char name[] = "empty";
    int score = 0;
    for (i = 1; i <= 11; ++i) {
        fwrite(&name, sizeof(char), 30, highscore);
        fwrite(&score, sizeof(int), 1, highscore);
    }
    fclose(highscore);
}

SCORE** get_scores() {
    FILE *highscore;
    highscore = fopen("highscore.dat", "r");

    SCORE *p;
    SCORE **scores = (SCORE**)malloc(11*sizeof(SCORE*));

    int i;
    char name[30];
    int scr;

    for (i = 0; i < 11; ++i) {
        p = (SCORE*)malloc(sizeof(SCORE));
        fread(&name, sizeof(char), 30, highscore);
        fread(&scr, sizeof(int), 1, highscore);
        strcpy(p->name, name);
        p->score = scr;
        scores[i] = p;
        //printf("%s %d\n", scores[i]->name, scores[i]->score);
    }
    fclose(highscore);
    return scores;
}

void save_highscore(SCORE** scores) {
    FILE*highscore;
    highscore = fopen("highscore.dat", "w");

    int i;
    for (i = 0; i < 11; ++i) {
        fwrite(&scores[i]->name, sizeof(char), 30, highscore);
        fwrite(&scores[i]->score, sizeof(int), 1, highscore);
    }
    //qsort(scores, 11, sizeof(SCORE*), vergleich);
    //bubble_sort(scores, 11);
    fclose(highscore);
}

void add_score(char* name, int score) {
    SCORE** scores;
    scores = get_scores();

    strcpy(scores[10]->name, name);
    scores[10]->score = score;

    bubble_sort(scores, 11);
    save_highscore(scores);
}

void highscore() {
    SCORE** scores;
    scores = get_scores();
    int i;
    for (i = 0; i < 10; ++i) {
        printf("%s %d\n", scores[i]->name, scores[i]->score);
        free(scores[i]);
    }
}
