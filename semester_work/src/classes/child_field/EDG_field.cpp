using namespace std;

#include "EDG_field.h"

EDG_field::EDG_field() : field(){
}

EDG_field::~EDG_field(){
}

string EDG_field::name() const {
	return "EDG";
}

string EDG_field::sprite() const {
	return "''''";
}

 shared_ptr<field> EDG_field::clone() const {
	return make_shared<EDG_field>(EDG_field());
}