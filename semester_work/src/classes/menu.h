#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <ostream>

//#include "graphical_api.h"
#include <ncurses.h>

#include "includes.h"

/// Menu parent class
/// 
/// provides template for working with menus, with both functionality and graphical implementation
class Menu {
public:
	Menu();
	Menu( WINDOW* &win, vector<string> add_items);
	virtual ~Menu() = default;

	int deploy(WINDOW*& win);

protected:

	int print_menu(WINDOW*& win, int a);

	void highlight(WINDOW*& win, int a);
	vector<string> items;
};