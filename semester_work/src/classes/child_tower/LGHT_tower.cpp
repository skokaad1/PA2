using namespace std;
#include "LGHT_tower.h"

LGHT_tower::LGHT_tower() : tower() {
}

LGHT_tower::~LGHT_tower() {
}

string LGHT_tower::sprite() const {
	return "~~||";
}

shared_ptr<tower> LGHT_tower::clone() const {
	return make_shared<LGHT_tower>(LGHT_tower());
}

