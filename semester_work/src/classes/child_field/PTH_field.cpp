using namespace std;
#include "PTH_field.h"

PTH_field::PTH_field() : field() {
}

PTH_field::~PTH_field() {
}

string PTH_field::name() const {
	return "PTH";
}

string PTH_field::sprite() const {
	return "    ";
}

 shared_ptr<field> PTH_field::clone() const {
	return make_shared<PTH_field>(PTH_field());
}