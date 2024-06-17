#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

extern void print(void);

int main() { 
    int key;
    int a = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

    do {
        usleep(500000);             // Espera 500 milisegundos
        clear();                    // Limpia la pantalla
        print();
        if (a == 0) {
            printw("a");
        } else {
            printw("b");
        }

        if ((key = getch()) != ERR) {                     
            if (key == KEY_UP) {
                printw("up");
                print();
            } else if (key == KEY_LEFT) {
                printw("left");
                print();
            } else if (key == KEY_RIGHT) {
                printw("right");
                print();
            } else if (key == KEY_DOWN) {
                printw("down");
                print();
            }
        }
        refresh();
    } while (1);

    endwin();
    return 0;
}
