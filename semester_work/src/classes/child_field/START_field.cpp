using namespace std;

#include "START_field.h"

START_field::START_field() : PTH_field() {
}

START_field::~START_field(){
}

string START_field::name() const {
	return "START";
}

string START_field::sprite() const {
	return "<-  ";
}

 shared_ptr<field> START_field::clone() const {
	return make_shared<START_field>(START_field());
}