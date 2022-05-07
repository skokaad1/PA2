using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include "includes.h"
#include <curses.h>
#include <string.h>
#include "menu.h"

#include "child_menu/START_menu.h"


/// window -- graphical api/engine
/// 
/// window class will serve as graphical/engine, made with the library ncurses
/// it provides the game with menu switch, graphical representation and sprite/map/menu incorporation
class window {
 private:
 public:
     window() {
         initscr();
         noecho();
         keypad(stdscr, TRUE);
         curs_set(0);
         cbreak();


         getmaxyx(stdscr, y_max, x_max);
         win = newwin(38, 120, 0, 0);
         box(win, 0, 0);
         mvwprintw(win, 19, 45, "PRESS A KEY TO START THE GAME");
         wgetch(win);
     }
     ~window() {
         endwin();
     }

     void StartMenu() {
         //START_menu start_menu = START_menu(win);
         current = START_menu(win);
         while (1) {
             //start_menu.deploy();
             int mcase = current.deploy();
             if (mcase == 1) { //New Game

             }
             if (mcase == 2) {

             }
             if (mcase == 3) {

             }
             if (mcase == 4) {

             }

         }
     }
 private:
     int y_max;
     int x_max;
     WINDOW* win;
     Menu current = Menu();
};


