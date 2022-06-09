
using namespace std;

#include "menu.h"
	
	int Menu::print_menu(WINDOW*& win,int a) {
		int counter = MENU_SPACING;
		box(win, 0, 0);
		int pos_of_a;
		int counter_ofitems = 0;
		for (string item : items) {
			if (counter_ofitems == a) {
				pos_of_a = counter;
			}
			counter_ofitems++;

			mvwaddstr(win, 0, counter, item.c_str());
			counter += item.length() + MENU_SPACING;
		}
		return pos_of_a;
	}

	void Menu::highlight(WINDOW*& win,int a) {
		int position = print_menu(win,a);
		wattron(win, A_STANDOUT);
		mvwprintw(win, 0, position, items[a].c_str());
		wattroff(win, A_STANDOUT);
	}

	Menu::Menu() {

	}
	Menu::Menu( WINDOW* &win,vector<string> add_items) {
		for (string new_item : add_items) {
			items.push_back(new_item);
		}
		highlight(win,0);
	}

	int Menu::deploy(WINDOW*& win) {
		wclear(win);
		while (1) {
			int input;
			long unsigned int selected = 0;
			highlight(win,0);
				while (1) {
					input = wgetch(win);
					if (input == 97) {
						selected--;
						if (selected > items.size() - 1) {
							selected = items.size()-1;
						}
						highlight(win,selected);
					}
					if (input == 100) {
						selected++;
						if (selected > items.size()-1) {
							selected = 0;
						}
						highlight(win,selected);
					}
					if (input == 10) {	
						return selected;
					}
				}
		}
	}

