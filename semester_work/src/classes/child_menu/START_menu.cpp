using namespace std;

#include "START_menu.h"

	START_menu::START_menu(WINDOW* in_win) : Menu() {
		win = in_win;
		items = { "New","Continue","Load Game","Load Unit" };
		highlight(0);
	}



