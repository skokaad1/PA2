#pragma once

using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include "includes.h"
#include <curses.h>
#include <string.h>
#include "menu.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>


#include "engine.cpp"

#include "child_menu/START_menu.h"


/// window -- graphical api/engine
/// 
/// window class will serve as graphical/engine, made with the library ncurses
/// it provides the game with menu switch, graphical representation and sprite/map/menu incorporation
class window {
 private:
 public:
     window();
     ~window();

     void StartMenu();
 private:
     int y_max;
     int x_max;
     WINDOW* win;
     Menu current = Menu();
     int term;
};


