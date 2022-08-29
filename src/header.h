#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#define DLINAPOLYA 81
#define VISOTAPOLYA 26
#define MIDDLEX (DLINAPOLYA / 2)
#define MIDDLEY (VISOTAPOLYA / 2)
#define STARTY 1
#define NACHALOPOLYA (STARTY + 1)

int next_x (int xx, int dxx);

int next_y (int yy, int dyy);

int collision_l (int xx, int yy, int dxx, int dyy, int lyy);

int collision_r (int xx, int yy, int dxx, int dyy, int ryy);

int touch_x(int dxx);

int touch_y(int dyy);

int goal_l(int xx);

int goal_r(int xx);

int high_score(int left_score, int right_score);

void filler(char symb);

void frame(int visota_left_racket, int visota_right_racket, int ball_x_coordinate, int ball_y_coordinate, int left_score, int right_score);

void draw_line_no_ball(char left, char right);

void draw_line_with_ball(char left, char right, int ball_x_coordinate);

void draw_line_score(int left_score, int right_score);

static int getch(void);
