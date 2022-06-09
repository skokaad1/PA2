#pragma once

#include <vector>
#include <random>

#include "child_tower/towers.h"

class Pre_made_storage {
private:
	int Random_num(int min, int  max, int seed);

public:
	Pre_made_storage();
	~Pre_made_storage();

	vector<pair<int, int>> random_path();

	shared_ptr<tower> random_tower();

private:
	vector<vector<pair<int, int>>> Storage;
	vector<shared_ptr<tower>> tower_template;
};