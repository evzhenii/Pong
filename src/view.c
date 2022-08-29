#include "header.h"

void filler(char symb);
void frame(int visota_left_racket, int visota_right_racket, int ball_x_coordinate, int ball_y_coordinate, int left_score, int right_score);
void draw_line_no_ball(char left, char right);
void draw_line_with_ball(char left, char right, int ball_x_coordinate);
void draw_line_score(int left_score, int right_score);
int animation();

void frame(int visota_left_racket, int visota_right_racket, int ball_x_coordinate, int ball_y_coordinate, int left_score, int right_score) {
    // otrisovka
    for (int y = 0; y <= VISOTAPOLYA; y++) {
        if (ball_y_coordinate == y) {
            if ((y == visota_left_racket || y == visota_left_racket - 1 || y == visota_left_racket + 1) &&
                (y == visota_right_racket || y == visota_right_racket - 1 || y == visota_right_racket + 1)) {
                draw_line_with_ball('|', '|', ball_x_coordinate);
            } else if ((y == visota_left_racket || y == visota_left_racket - 1 || y == visota_left_racket + 1) &&
                       (y != visota_right_racket && y != visota_right_racket - 1 && y != visota_right_racket + 1)) {
                draw_line_with_ball('|', ' ', ball_x_coordinate);
            } else if ((y != visota_left_racket && y != visota_left_racket - 1 && y != visota_left_racket + 1) &&
                       (y == visota_right_racket || y == visota_right_racket - 1 || y == visota_right_racket + 1)) {
                draw_line_with_ball(' ', '|', ball_x_coordinate);
            } else {
                draw_line_with_ball(' ', ' ', ball_x_coordinate);
            }
        } else {
            if (y == 0 && y < STARTY) {
                printf("            LEFT PLAYER SCORE: %d                 RIGHT PLAYER SCORE: %d           \n", left_score, right_score);
            } else if (y == STARTY || y == VISOTAPOLYA) {
                filler('-');
            } else if((y == visota_left_racket || y == visota_left_racket - 1 || y == visota_left_racket + 1) &&
                    (y == visota_right_racket || y == visota_right_racket - 1 || y == visota_right_racket + 1)) {
                draw_line_no_ball('|', '|');
            } else if ((y == visota_left_racket || y == visota_left_racket - 1 || y == visota_left_racket + 1) &&
                       (y != visota_right_racket && y != visota_right_racket - 1 && y != visota_right_racket + 1)) {
                draw_line_no_ball('|', ' ');
            } else if ((y != visota_left_racket && y != visota_left_racket - 1 && y != visota_left_racket + 1) &&
                       (y == visota_right_racket || y == visota_right_racket - 1 || y == visota_right_racket + 1)) {
                draw_line_no_ball(' ', '|');
            } else {
                draw_line_no_ball(' ', ' ');
            }
        }
    }
}

void draw_line_no_ball(char left, char right) {
    char space = ' ';
    char vertical = '|';
    for (int i = 0; i <= DLINAPOLYA; i++) {
        if (i == 2) {
            printf("%c", left);
        }
        if (i == DLINAPOLYA - 2) {
            printf("%c", right);
        }
        if (i == MIDDLEX) {
            printf("%c", vertical);
        } else {
            printf("%c", space);
        }
    }
    printf("\n");
}

void draw_line_with_ball(char left, char right, int ball_x_coordinate) {
    char space = ' ';
    char ball = 'o';
    char vertical = '|';
    for (int i = 0; i <= DLINAPOLYA; i++) {
        if (i == 2) {
            printf("%c", left);
        }
        if (i == DLINAPOLYA - 2) {
            printf("%c", right);
        }
        if (i == MIDDLEX && ball_x_coordinate != MIDDLEX) {
            printf("%c", vertical);
        } else if (i == ball_x_coordinate) {
            printf("%c", ball);
        } else {
            printf("%c", space);
        }
    }
    printf("\n");
}

void filler(char symb) {
    for (int i = 0; i <= DLINAPOLYA; i++) {
        printf("%c", symb);
    }
    printf("\n");
}

