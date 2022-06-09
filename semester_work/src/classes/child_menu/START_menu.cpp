using namespace std;

#include "START_menu.h"

	START_menu::START_menu( WINDOW* &win) : Menu() {
		//win = in_win;
		items = { "New","Continue","Load Game","Load Unit" };
		highlight(win,0);
	}



