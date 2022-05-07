
using namespace std;

#include "menu.h"
	/*void print_menu() {
		int counter = 2;
		box(win, 0, 0);
		for (string item : items) {
			mvwaddstr(win, 0, counter, item.c_str());
			counter += item.length() + 2;
		}
	}*/
	
	int Menu::print_menu(int a) {
		int counter = 2;
		box(win, 0, 0);
		int pos_of_a;
		int counter_ofitems = 0;
		for (string item : items) {
			if (counter_ofitems == a) {
				pos_of_a = counter;
			}
			counter_ofitems++;

			mvwaddstr(win, 0, counter, item.c_str());
			counter += item.length() + 2;
		}
		return pos_of_a;
	}

	void Menu::highlight(int a) {
		int position = print_menu(a);
		wattron(win, A_STANDOUT);
		mvwprintw(win, 0, position, items[a].c_str());
		wattroff(win, A_STANDOUT);
	}

	Menu::Menu() {

	}
	Menu::Menu(WINDOW* in_win,vector<string> add_items) {
		win = in_win;
		for (string new_item : add_items) {
			items.push_back(new_item);
		}
		highlight(0);
	}

	int Menu::deploy() {
		wclear(win);
		while (1) {
			int input;
			long unsigned int selected = 0;
			highlight(0);
				while (1) {
					input = wgetch(win);
					//cout << input << endl;
					if (input == 97) {
						selected--;
						if (selected > items.size() - 1) {
							selected = items.size()-1;
						}
						highlight(selected);
					}
					if (input == 100) {
						selected++;
						if (selected > items.size()-1) {
							selected = 0;
						}
						highlight(selected);
					}
					if (input == 10) {	
						return selected;
					}
				}
		}
	}

