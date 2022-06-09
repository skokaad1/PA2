using namespace std;

#include "graphical_api.h"


window::window() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    start_color();

    getmaxyx(stdscr, y_max, x_max);
    win = newwin(38, 120, 0, 0);

    box(win, 0, 0);
    mvwprintw(win, 19, 45, "PRESS A KEY TO START THE GAME");
    wgetch(win);
}
window::~window() {
    endwin();
    //free_window(win);
}

int window::StartMenu() {
    START_menu start_menu = START_menu(win);
    current = START_menu(win);
    while (1) {
        int input = 0;
        int mcase = current.deploy(win);
        //int mcase = current.deploy(win);
        if (mcase == 0) { //New Game
            engine New_game = engine(win);
            input = New_game.start(win);
        }
        if (mcase == 1) { //Continue

        }
        if (mcase == 2) { //Load File

        }
        if (mcase == 3) {

        }
        if (input == EXIT) {
            return EXIT;
        }
    }
        return 1;
}



