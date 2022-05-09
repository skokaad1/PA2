using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include "includes.h"
#include <curses.h>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <ncurses.h>

#include "field.h"
#include "child_field/fields.h"



class engine {
private:
	struct Node {
		shared_ptr<field> build_field;

		Node &Left;
		Node &Down;
		Node &Up;
		Node &Right;
	};

public:

	void map_create() {


		for (int i = 0; i < MAP_X + 2; i++) {
			for (int k = 0; k < MAP_Y + 2; k++) {
				grid[i][k].build_field = make_shared<BCK_field>(BCK_field());
			}
		}

		for (int i = 0; i < MAP_X + 2; i++) {
			grid[i][0].build_field = make_shared<EDG_field>(EDG_field());
			grid[i][MAP_Y + 1].build_field = make_shared<EDG_field>(EDG_field());
		}
		for (int i = 0; i < MAP_Y + 2; i++) {
			grid[0][i].build_field = make_shared<EDG_field>(EDG_field());
			grid[MAP_X + 1][i].build_field = make_shared<EDG_field>(EDG_field());
		}

		grid[0][(rand() % MAP_Y) + 2].build_field = make_shared<END_field>(END_field());

	}

	engine(WINDOW* inc_win) {
		win = inc_win;
		wclear(win);
		box(win, 0, 0);

	}

	void one_block(string image, int y_anchor, int x_anchor) {
		string a = image.substr(0, 2);
		string b = image.substr(2, 2);
		mvwprintw(win, y_anchor, x_anchor, a.c_str());
		mvwprintw(win, y_anchor + 1, x_anchor, b.c_str());

	}

	void Print_grid() {
		for (int i = 0; i < MAP_X + 2; i++) {
			for (int k = 0; k < MAP_Y + 2; k++) {
				one_block(grid[i][k].build_field->sprite(), 2 + (k * 2), 3 + (i * 2));
			}
		}
	}

	void start() {
		int test = 0;
		map_create();
		Print_grid();
		while (1) {
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();;
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			sleep(0.1 / (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()));
			wrefresh(win);
			box(win, 0, 0);
			test++;
		}
	}

private:
	WINDOW* win;
	Node grid[MAP_X + 2][ MAP_Y + 2];
};



