using namespace std;
#include "BSC_tower.h"


BSC_tower::BSC_tower() : tower() {
}

BSC_tower::~BSC_tower() {
}

string BSC_tower::sprite() const {
	return "/\\||";
}

shared_ptr<tower> BSC_tower::clone() const {
	return make_shared<BSC_tower>(BSC_tower());
}

