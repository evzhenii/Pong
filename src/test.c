int main() {
    int i;
    initscr();
    halfdelay(5);
    for (i=0; i < 5; i++)
        getch();
    endwin();
}
