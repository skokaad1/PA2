#pragma once

#include "../menu.h"
#include <curses.h>

class START_menu : public Menu {
public:
	START_menu(WINDOW* in_win);
};