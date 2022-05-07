using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include "includes.h"
#include <curses.h>
#include <string.h>


/// window -- graphical api/engine
/// 
/// window class will serve as graphical/engine, made with the library ncurses
/// it provides the game with menu switch, graphical representation and sprite/map/menu incorporation
class window {
 private:
     void highlight_menu(const char* name, int x) {
         mvwprintw(win, 0, 2, "[N]New");
         mvwprintw(win, 0, 10, "[C]Continue");
         mvwprintw(win, 0, 23, "[G]Load Game");
         mvwprintw(win, 0, 37, "[U]Load Unit");
         wattron(win, A_STANDOUT);
         mvwprintw(win, 0, x, name);
         wattroff(win, A_STANDOUT);
     }
 public:
     window() {
         initscr();
         noecho();
         curs_set(0);
         cbreak();


         getmaxyx(stdscr, y_max, x_max);
         win = newwin(38, 120, 0, 0);
         box(win, 0, 0);

         mvwprintw(win, 0, 2, "[N]New");
         mvwprintw(win, 0, 10, "[C]Continue");
         mvwprintw(win, 0, 23, "[G]Load Game");
         mvwprintw(win, 0, 37, "[U]Load Unit");
         wgetch(win);
     }
     ~window() {
         endwin();
     }
     void Newgame() {
     }
     void Continue() {
     }
     void Load_game() {
     }
     void Load_unit() {
     }

     void StartMenu() {
         while (1) {
             char input;
             char selected;
             while (1) {
                 input = wgetch(win);
                 input = tolower(input);
                 switch (input) {
                    case'n':
                        highlight_menu("[N]New", 2);
                        selected = 'n';
                        break;
                    case'c':
                        highlight_menu("[C]Continue", 10);
                        selected = 'c';
                        break;
                    case'g':
                        highlight_menu("[G]Load Game", 23);
                        selected = 'g';
                        break;
                    case'u':
                        highlight_menu("[U]Load Unit", 37);
                        selected = 'u';
                        break;
                    case'\n':
                        switch (selected) {
                            case 'n':
                                Newgame();
                                break;
                            case 'c':
                                Continue();
                                break;
                            case 'g':
                                Load_game();
                                break;
                            case 'u':
                                Load_unit();
                                break;
                        }
                        break;
                 }
             }
         }
     }
 private:
     int y_max;
     int x_max;
     WINDOW* win;
};


