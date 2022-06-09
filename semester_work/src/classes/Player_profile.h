#pragma once

//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "child_invader/invaders.h"


class profile {
private:

public:
	profile();

	~profile();
	

	void get_team(vector<shared_ptr<invader>>& team) const;

private:
	vector<shared_ptr<invader>> unlocked;
	vector<shared_ptr<invader>> team;
};



