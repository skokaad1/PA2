#pragma once

#include "../menu.h"
#include <curses.h>
#include "../Player_profile.h"

class GAME_menu : public Menu {
public:
	GAME_menu( WINDOW* &win, profile player);

	int start(WINDOW*& win, vector<shared_ptr<invader>> &deployed);

	pair<int,int> deploy(WINDOW*& win);

	void one_block(WINDOW*& win, string image, int y_anchor, int x_anchor);

	void column_h(WINDOW*& win, int column, int row);

	void row_h(WINDOW*& win, int column, int row);

	int print_row(WINDOW*& win, int row);

	int print_column(WINDOW*& win, int column,int row);
private:
	vector<vector<string>> selection;
	vector<shared_ptr<invader>> cur_team;
};