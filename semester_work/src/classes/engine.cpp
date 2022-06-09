using namespace std;

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <ncurses.h>

#include "field.h"
#include "child_field/fields.h"
#include "Player_profile.h"

#include "map_create.cpp"
#include "child_menu/GAME_menu.h"
#include "child_invader/invaders.h"

#include <random>
#include <vector>


/// game start and run
/// 
/// realizes base game loop, provides graphical realization of game elements, calls on map creation
class engine {
private:
	int Random_num(int min, int  max, int seed) {
		typedef std::mt19937 rng_type;
		std::uniform_int_distribution<rng_type::result_type> udist(min, max);
		rng_type rng;

		rng_type::result_type const seedval = time(0) + seed;

		rng.seed(seedval);

		rng_type::result_type random_number = udist(rng);
		return random_number;
	}

	public:

	engine(WINDOW* &win) {
		wclear(win);
		box(win, 0, 0);
	}

	~engine() {
	}

	void one_block(WINDOW*& win,string image, int y_anchor, int x_anchor) {
		string a = image.substr(0, 2);
		string b = image.substr(2, 2);
		mvwprintw(win, y_anchor, x_anchor, a.c_str());
		mvwprintw(win, y_anchor + 1, x_anchor, b.c_str());

	}

	void Print_grid(WINDOW*& win) {
		for (int i = 0; i < MAP_X + 2; i++) {
			for (int k = 0; k < MAP_Y + 2; k++) {
				one_block(win,grid[i][k]->sprite(), 4 + (k * 2), 5 + (i * 2));
			}
		}
	}

	int start(WINDOW*& win) { // 0 = terminate
		new_map generator = new_map(win, grid);
		vector<pair<int, int>> towers;
		vector<pair<int,int>> path = generator.build_map(grid, towers);
		long unsigned int moves = towers.size() * 2;
		vector<bool> turn = { 1 };
		vector<shared_ptr<invader>> deployed;
		profile player = profile();
		for (long unsigned int i = 1; i < moves; i++) {
			if (turn[i - 1] == 0) {
				turn.push_back(1);
			}
			else {
				turn.push_back(0);
			}
		}
		Print_grid(win);
		GAME_menu interface = GAME_menu(win,player);

		for (long unsigned int i = 0; i < moves; i++) {
			int input = 0;
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();;
			if (turn[i] == 1) {
				input = interface.start(win, deployed);
				if (input == EXIT) {
					return EXIT;
				}
				if (input == BACK) {
					return BACK;
				}
			}
			else {
			
			}
			Print_grid(win);
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			sleep(300 / (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()));
			wrefresh(win);
			//box(win, 0, 0);
		}
		return 1;
	}

private:
	int path_length;
	vector<vector<shared_ptr<field>>> grid;
};



