using namespace std;

//#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <ncurses.h>

#include "field.h"
#include "child_field/fields.h"
#include "child_tower/towers.h"
#include "pre_made.h"
#include "Player_profile.h"

#include <fstream>

#include <random>



class new_map {
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

	bool node_travel(pair<int,int> current, int path_length, vector<vector<shared_ptr<field>>>& grid,vector<pair<int,int>> &output) {
		if (grid[current.first-1][current.second]->name() == "END") {
			output.push_back(make_pair(current.first - 1, current.second) );
			output.push_back(current);
			return true;
		}

		path_length++;
		int counter = 0;
		int nextA = Random_num(0, 3, path_length);
		vector <int> pos = {1, 2, 3, 4};
		while (counter < 4) {
			int next = nextA + counter;
			if (next > 3) {
				next = next - 4;
			}
			pair<int, int> nextP = current;
			if (next == 0) {
				nextP.first += -1;
				counter++;
			}
			if (next == 1) {
				nextP.second += 1;
				counter++;
			}
			if (next == 2) {
				nextP.second += -1;
				counter++;
			}
			if (next == 3) {
				nextP.first += 1;
				counter++;
			}
			if (grid[nextP.first][nextP.second]->name() == "BCK") {
				if (
					((grid[nextP.first - 1][nextP.second]->name() != "PTH") || (nextP.first - 1 == current.first && nextP.second == current.second)) &&
					((grid[nextP.first + 1][nextP.second]->name() != "PTH") || (nextP.first + 1 == current.first && nextP.second == current.second)) &&
					((grid[nextP.first][nextP.second - 1]->name() != "PTH") || (nextP.first == current.first && nextP.second - 1 == current.second)) &&
					((grid[nextP.first][nextP.second + 1]->name() != "PTH") || (nextP.first == current.first && nextP.second + 1 == current.second))
					){
					grid[nextP.first][nextP.second] = PTH_field().clone();
					if (node_travel(nextP, path_length, grid, output) == true) {
						output.push_back(current);
						return true;
					}
					else {
						grid[nextP.first][nextP.second] = BCK_field().clone();
					}
				}
			}
		}
		return false;
	}

public:
	void path_create(vector<vector<shared_ptr<field>>>& grid) {

		grid[0][Random_num(1, MAP_Y, 1)] = END_field().clone();

		int start = Random_num(1, MAP_Y, 2);
		grid[MAP_X + 1][start] = START_field().clone();

		path_length = 0;
		vector<pair<int, int>> output = {};
		
		pair<int,int> current = make_pair( MAP_X, start);
		grid[current.first][current.second] = PTH_field().clone();
		while (node_travel(current, path_length, grid, output) == false) {
			path_length = 0;
		}

		output.push_back(make_pair(MAP_X + 1, start));

		ofstream MyFile("Path.txt");
		
		MyFile << "Path Test" << endl;

		for (long unsigned int i = 0; i < output.size(); i++) {
			MyFile << "{" << output[i].first << "," << output[i].second << "}, " <<  endl;
		}
		MyFile.close();
	}

	vector<pair<int, int>> build_map(vector<vector<shared_ptr<field>>> & grid, vector<pair<int, int>> &towers) {
		vector<pair<int,int>> path = Pre_made_storage().random_path();
		for (auto pair : path) {
			if (pair.first == 0) {
				grid[pair.first][pair.second] = START_field().clone();
			}
			else if (pair.first == MAP_X + 1) {
				grid[pair.first][pair.second] = END_field().clone();
			}
			else {
				grid[pair.first][pair.second] = PTH_field().clone();
			}
		}
		long unsigned turrets = 0;
		int step = 10;
		for (long unsigned int i = 9; i < path.size(); i += step) {
			bool success = 1; 
			if (turrets == path.size() / step) {
				break;
			}
			while (success) {
				if (path[i].first + 2 < MAP_X + 1)
					if (grid[path[i].first + 2][path[i].second]->name() == "BCK") {
						grid[path[i].first + 2][path[i].second] = TWR_field().clone();
						success = 0;
						turrets++;
						towers.push_back(make_pair(path[i].first + 2,path[i].second));
					}
				if (path[i].first - 2 > 1) {
					if (grid[path[i].first - 2][path[i].second]->name() == "BCK") {
						grid[path[i].first - 2][path[i].second] = TWR_field().clone();
						success = 0;
						turrets++;
						towers.push_back(make_pair(path[i].first - 2, path[i].second));
					}
				}
				if (path[i].second + 2 < MAP_Y + 1) {
					if (grid[path[i].first][path[i].second + 2]->name() == "BCK") {
						grid[path[i].first][path[i].second + 2] = TWR_field().clone();
						success = 0;
						turrets++;
						towers.push_back(make_pair(path[i].first, path[i].second + 2));
					}
				}
				if (path[i].second - 2 > 1) {
					if (grid[path[i].first][path[i].second - 2]->name() == "BCK") {
						grid[path[i].first][path[i].second - 2] = TWR_field().clone();
						success = 0;
						turrets++;
						towers.push_back(make_pair(path[i].first, path[i].second - 2));
					}
				}
				i++;
				if ( !( i < path.size() ) ) {
					success = 0;
					break;
				}
			}
		}
		//place_towers(towers, grid);
		return path;
	}

	new_map(WINDOW* &win , vector<vector<shared_ptr<field>>>& grid) {
		wclear(win);
		box(win, 0, 0);

		for (int i = 0; i < MAP_X + 2; ++i) {
			grid.push_back(vector<shared_ptr<field>> {});
			for (int k = 0; k < MAP_Y + 2; ++k) {
				grid[i].push_back(BCK_field().clone());
			}
		}

		for (int i = 0; i < MAP_X + 2; ++i) {
			grid[i][0] = EDG_field().clone();
			grid[i][MAP_Y + 1] = EDG_field().clone();
		}
		for (int i = 0; i < MAP_Y + 2; ++i) {
			grid[0][i] = EDG_field().clone();
			grid[MAP_X + 1][i] = EDG_field().clone();
		}

	}

	~new_map() {
	}


private:
	int path_length;
};



