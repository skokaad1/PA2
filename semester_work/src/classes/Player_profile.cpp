using namespace std;

//#include <stdlib.h>
#include "Player_profile.h"

profile::profile() {
	unlocked.push_back(ARM_invader().clone());
	unlocked.push_back(INT_invader().clone());
	unlocked.push_back(SCT_invader().clone());
	for (shared_ptr<invader> one : unlocked) {
		team.push_back(one->clone());
	}
}

profile::~profile() {
	
}

void profile::get_team(vector<shared_ptr<invader>> &outteam) const {
	for (shared_ptr<invader> one : unlocked) {
		outteam.push_back(one->clone());
	}
}


