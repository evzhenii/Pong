#include "header.h"

int next_x (int xx, int dxx) {
    xx = xx + dxx;
    return(xx);
}
static struct termios term, oterm;
static int getch(void) {
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

int next_y (int yy, int dyy) {
    yy = yy + dyy;
    return(yy);
}

int collision_l (int xx, int yy, int dxx, int dyy, int lyy) {
    int f = 0;
    if (xx == 4 && dxx == -1) {
        if (dyy == -1) {
            if (yy == (lyy+2)) {
                f = 1;
            }
            if (yy == lyy || yy == lyy+1) {
                f = 2;
            }
        }
        if (dyy == 1) {
            if (yy == (lyy+2)) {
                f = 1;
            }
            if (yy == lyy || yy == lyy+1) {
                f = 2;
            }
        }
    }
    return(f);
}

int collision_r (int xx, int yy, int dxx, int dyy, int ryy) {
    int f = 0;
    if (xx == 76 && dxx == 1) {
        if (dyy == -1) {
            if (yy == (ryy+2)) {
                f = 1;
            }
            if (yy == ryy || yy == ryy+1) {
                f = 2;
            }
        }
        
        if (dyy == 1) {
            if (yy == (ryy-2)) {
                f = 1;
            }
            if (yy == ryy || yy == ryy-1) {
                f = 1;
            }
        }
    }
}

int touch_x(int dxx) {
    return(-dxx);
}

int touch_y(int dyy) {
    return(-dyy);
}

int goal_l(int xx) {
    if (xx == 1) {
        return(1);
    }
    return(0);
}

int goal_r(int xx) {
    if (xx == 79) {
        return(1);
    }
    return(0);
}

int high_score(int left_score, int right_score) {
    if (left_score >= right_score) { return left_score }
    else { return right_score}
}
