using namespace std;

#include "field.h"

field::field() {

}

string field::name() const {
	return "ERR";
}

string field::sprite() const {
	stringstream ss;
	for (int i = 0; i < FIELD_X + FIELD_Y; i++) {
		ss << ".";
	}
	return ss.str();
}