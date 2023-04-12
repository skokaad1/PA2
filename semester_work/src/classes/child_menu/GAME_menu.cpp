using namespace std;

#include "GAME_menu.h"

	GAME_menu::GAME_menu( WINDOW* &win , profile player) : Menu() {
		//win = in_win;
		items = { "Back","Exit" };
		selection.push_back(items);
		player.get_team(cur_team);
		for (shared_ptr<invader> i : cur_team) {
			selection.push_back({ "Deploy","Move","Special" });
		}
	}

	void GAME_menu::one_block(WINDOW*& win, string image, int y_anchor, int x_anchor) {
		string a = image.substr(0, 2);
		string b = image.substr(2, 2);
		mvwprintw(win, y_anchor, x_anchor, a.c_str());
		mvwprintw(win, y_anchor + 1, x_anchor, b.c_str());

	}

	int GAME_menu::print_column(WINDOW*& win, int column,int row) {
		long unsigned int counter = MENU_SPACING + 4;
		int pos_of_column = 0;
		int counter_ofitems = 0;
		for (long unsigned int i = 0; i < selection[row].size(); i++) {
			if (counter_ofitems == column) {
				pos_of_column = counter;
			}
			counter_ofitems++;
			mvwprintw(win, W_HEIGHT - 3, counter, selection[row][i].c_str());
			counter += selection[row][i].size() + + MENU_SPACING;
		}
		return pos_of_column;
	}

	void GAME_menu::column_h(WINDOW*& win, int column, int row) {
		int position = print_column(win, column, row);
		print_menu(win, 0);
		wattron(win, A_STANDOUT);
		mvwprintw(win, W_HEIGHT - 3 , position, selection[row][column].c_str());
		wattroff(win, A_STANDOUT);
	}

	int GAME_menu::print_row(WINDOW*& win, int row) {
		int counter = MENU_SPACING + 2;
		int pos_of_row = 1;
		int counter_ofitems = 1;
		for (long unsigned int i = 1; i < selection.size(); i++){
			if (counter_ofitems == row) {
				pos_of_row = counter;
			}
			counter_ofitems++;

			one_block(win, cur_team[i - 1]->sprite(), counter, W_LENGTH-5);
			counter += 1+ MENU_SPACING;
		}
		return pos_of_row;
	}

	void GAME_menu::row_h(WINDOW*& win, int column, int row) {
		column_h(win, column, row);
		int position = print_row(win, row);
		print_menu(win, 0);
		wattron(win, A_STANDOUT);
		one_block(win, cur_team[row-1]->sprite(), position, W_LENGTH - 5);
		wattroff(win, A_STANDOUT);
	}

	pair<int,int> GAME_menu::deploy(WINDOW*& win){
		//wclear(win);
		while (1) {
			int input;
			long unsigned int selected_column = 0;
			long unsigned int selected_row = 1;
			print_menu(win, 0);
			row_h(win, selected_column, selected_row);
			//highlight(win, 0);
			while (1) {
				input = wgetch(win);
				if (input == 97) { //a
					selected_column--;
					if (selected_column > selection[selected_row].size() - 1) {
						selected_column = selection[selected_row].size() - 1;
					}
					if (selected_row == 0) {
						print_row(win, selected_row);
						print_column(win, 1, 1);
						highlight(win, selected_column);
					}
					else {
						column_h(win, selected_column, selected_row);
					}
				}
				if (input == 100) { //d
					selected_column++;
					if (selected_column > selection[selected_row].size() - 1) {
						selected_column = 0;
					}
					if (selected_row == 0) {
						print_row(win, selected_row);
						print_column(win, 1, 1);
						highlight(win, selected_column);
					}
					else {
						column_h(win, selected_column, selected_row);

					}
				}
				if (input == 115) { //s
					selected_row++;
					if (selected_row > selection.size() - 1) {
						selected_row = 0;
					}
					if (selected_row == 0) {
						selected_column = 0;
						print_row(win, selected_row);
						print_column(win, 1, 1);
						highlight(win, 0);
					}
					else {
						row_h(win, selected_column, selected_row);
					}
				}
				if (input == 119) { //ws
					selected_row--;
					if (selected_row > selection.size() - 1) {
						selected_row = selection.size() - 1;
					}
					if (selected_row == 0) {
						selected_column = 0;
						print_row(win, selected_row);
						print_column(win, 1, 1);
						highlight(win, 0);
					}
					else {
						row_h(win, selected_column, selected_row);
					}
				}

				if (input == 10) {
					return make_pair(selected_row,selected_column);
				}
			}
		}
	}

	int GAME_menu::start(WINDOW*& win, vector<shared_ptr<invader>> &deployed, vector<vector<shared_ptr<field>>>& grid, vector<pair<int, int>> &path) { // 0 = Exit // 0 = back
		pair<int,int> input = deploy(win);
		if (input.first == 0) {
			if (input.second == 0) {
				return BACK;
			}
			if (input.second == 1) {
				return EXIT;
			}
		}
		else {
			if (input.second == 0) { //deploy
				int i = 0;
				//mvwprintw(win, W_HEIGHT - 3, 0, "HELP MEEEEEEEEEEEEEEEEEE");
				shared_ptr<invader> unit = cur_team[input.first-1]->deploy(i);
				unit = cur_team[input.first - 1]->clone();
				//mvwprintw(win, 2, 0, unit->sprite().c_str());
				grid[path[i].first][path[i].second]->inhabit(unit);
				mvwprintw(win, 2, 0, grid[path[i].first][path[i].second]->sprite().c_str());
			}
			if (input.second == 1) { // move
			
			}
			if (input.second == 2) { // special
			
			}
		}
		return -1;
	}


