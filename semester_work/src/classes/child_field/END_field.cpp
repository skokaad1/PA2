using namespace std;

#include "END_field.h"

END_field::END_field() : field() {
}

END_field::~END_field(){
}

string END_field::name() const {
	return "END";
}

string END_field::sprite() const {
	return "<-  ";
}

 shared_ptr<field> END_field::clone() const {
	return make_shared<END_field>(END_field());
}