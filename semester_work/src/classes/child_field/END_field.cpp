using namespace std;

#include "END_field.h"

END_field::END_field() : field() {
}

string END_field::name() const {
	return "BCK";
}

string END_field::sprite() const {
	return "<=__";
}