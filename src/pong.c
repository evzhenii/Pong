//I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#define DLINAPOLYA 81
#define VISOTAPOLYA 26
#define LEFTRACKETX 3
#define RIGHTRACKETX 77
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
int high_score(int left_score, int right_score);
void filler(char symb);
void frame(int visota_left_racket, int visota_right_racket, int ball_x_coordinate, int ball_y_coordinate, int left_score, int right_score);
void draw_line_no_ball(char left, char right);
void draw_line_with_ball(char left, char right, int ball_x_coordinate);
void draw_line_score(int left_score, int right_score);

int main(void) {
    int visota_left_racket = MIDDLEY;
    int visota_right_racket = MIDDLEY;
    int igra_do_talogo = 1;
    int left_score = 0;
    int right_score = 0;
    int otrazheniye = 0;
    
    // schitivaniye keyboard
//    noecho();
    halfdelay(5);
    int scaninput() {
        int loop = 1;
        while (loop) {
            int key;
            key = getch();
            if (key == 'A' || key == 'a') {
                if (visota_left_racket > NACHALOPOLYA + 1) { visota_left_racket--; }
                // chtoto ne to no tak rabotayet
                loop = 0;
            } else if (key == 'Z' || key == 'z') {
                if (visota_left_racket < VISOTAPOLYA - 2) { visota_left_racket++; }
                // chtoto ne to no tak rabotayet
                loop = 0;
            } else if (key == 'K' || key == 'k') {
                if (visota_right_racket > NACHALOPOLYA + 1) { visota_right_racket--; }
                loop = 0;
            } else if (key == 'M' || key == 'm') {
                if (visota_right_racket < VISOTAPOLYA - 2) { visota_right_racket++; }
                loop = 0;
            } else if (key == ' ') {
                loop = 0;
            } else {
            //printf("end of scatf");
            loop = 0;
            }
        }
        return 0;
    }
    
    
    //game

    while (igra_do_talogo) {
        visota_left_racket = MIDDLEY;
        visota_right_racket = MIDDLEY;
        int ball_x_coordinate = MIDDLEX;
        int ball_y_coordinate = MIDDLEY;
        int igra_do_zabitogo = 1;
        int dx = -1;
        int dy = -1;
        
        while (igra_do_zabitogo) {
            int tick = 1;
            
            while (tick) {
                if ((ball_y_coordinate == 1 && dy == -1) || (ball_y_coordinate == 25 && dy == 1)) { dy = touch_y(dy); }
                otrazheniye = collision_l(ball_x_coordinate, ball_y_coordinate, dx, dy, visota_left_racket);
                if (otrazheniye == 1) {
                    dx = touch_x(dx);
                    dy = touch_y(dy);
                }
                if (otrazheniye == 2) { dx = touch_x(dx); }
                
                otrazheniye = collision_r(ball_x_coordinate, ball_y_coordinate, dx, dy, visota_right_racket);
                if (otrazheniye == 1) {
                    dx = touch_x(dx);
                    dy = touch_y(dy);
                }
                if (otrazheniye == 2) { dx = touch_x(dx); }
                if ((ball_y_coordinate == 1 && dy == -1) || (ball_y_coordinate == 25 && dy == 1)) { dy = touch_y(dy); }
                
                // goals
                
                if (ball_x_coordinate < 0) {
                    printf("right ++");
                    right_score++;
                    igra_do_zabitogo--;
                } else if (ball_x_coordinate > DLINAPOLYA) {
                    printf("left ++");
                    left_score++;
                    igra_do_zabitogo--;
                }
                
                //otrisovka
                //                printf("ball x = %d, ball y = %d.\n", ball_x_coordinate, ball_y_coordinate);
                frame(visota_left_racket, visota_right_racket, ball_x_coordinate, ball_y_coordinate, left_score, right_score);
                scaninput();
                usleep(500000);
                printf("\033[H\033[J");
                ball_x_coordinate = next_x(ball_x_coordinate, dx);
                ball_y_coordinate = next_y(ball_y_coordinate, dy);
                tick--;
            }
        }
        if (high_score(left_score, right_score) > 20) {
            igra_do_talogo--;
        }
    }
}


// CONTROLLER
//static struct termios term, oterm;
//static int getch(void) {
//    int c = 0;
//    tcgetattr(0, &oterm);
//    memcpy(&term, &oterm, sizeof(term));
//    VTIME(5);
//    term.c_lflag &= ~(ICANON | ECHO);
//    term.c_cc[VMIN] = 1;
//    term.c_cc[VTIME] = 0;
//    tcsetattr(0, TCSANOW, &term);
//    c = getchar();
//    tcsetattr(0, TCSANOW, &oterm);
//    return c;
//}

int next_x (int xx, int dxx) {
    xx += dxx;
    return(xx);
}

int next_y (int yy, int dyy) {
    yy += dyy;
    return(yy);
}

int collision_l (int xx, int yy, int dxx, int dyy, int visota_left_racket) {
    int touch_rocket_index = 0;
    if (xx == 4 && dxx == -1) {
        if (dyy == -1) {
            if (yy == (visota_left_racket+2)) {
                touch_rocket_index = 1;
            }
            if (yy == visota_left_racket || yy == visota_left_racket+1 || yy == visota_left_racket-1) {
                touch_rocket_index = 2;
            }
        }
        if (dyy == 1) {
            if (yy == (visota_left_racket+2)) {
                touch_rocket_index = 1;
            }
            if (yy == visota_left_racket || yy == visota_left_racket+1 || yy == visota_left_racket-1) {
                touch_rocket_index = 2;
            }
        }
    }
    return(touch_rocket_index);
}

int collision_r (int xx, int yy, int dxx, int dyy, int visota_right_racket) {
    int touch_rocket_index = 0;
    if (xx == 76 && dxx == 1) {
        if (dyy == -1) {
            if (yy == (visota_right_racket+2)) {
                touch_rocket_index = 1;
            }
            if (yy == visota_right_racket || yy == visota_right_racket+1 || yy == visota_right_racket-1) {
                touch_rocket_index = 2;
            }
        }
        
        if (dyy == 1) {
            if (yy == (visota_right_racket-2)) {
                touch_rocket_index = 1;
            }
            if (yy == visota_right_racket || yy == visota_right_racket+1 || yy == visota_right_racket-1) {
                touch_rocket_index = 1;
            }
        }
    }
    return touch_rocket_index;
}

int touch_x(int dxx) {
    return(-dxx);
}

int touch_y(int dyy) {
    return(-dyy);
}

int high_score(int left_score, int right_score) {
    if (left_score >= right_score) { return left_score; }
    else { return right_score; }
}

// VIEW

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
            if (y == 0 || y == VISOTAPOLYA) {
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
    printf("            LEFT PLAYER SCORE: %d                 RIGHT PLAYER SCORE: %d           \n", left_score, right_score);
}

void draw_line_no_ball(char left, char right) {
    char space = ' ';
    char vertical = '|';
    for (int i = 0; i <= DLINAPOLYA; i++) {
        if (i == LEFTRACKETX) {
            printf("%c", left);
        }
        if (i == RIGHTRACKETX) {
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
        if (i == LEFTRACKETX) {
            printf("%c", left);
        }
        if (i == RIGHTRACKETX) {
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
