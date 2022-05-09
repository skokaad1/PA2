#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <ostream>

#include "includes.h"

/// Menu parent class
/// 
/// provides template for working with menus, with both functionality and graphical implementation
class Menu {
public:
	Menu();
	Menu(WINDOW* in_win, vector<string> add_items);
	virtual ~Menu() = default;

	int deploy();

protected:

	int print_menu(int a);

	void highlight(int a);

	WINDOW* win;
	vector<string> items;
};