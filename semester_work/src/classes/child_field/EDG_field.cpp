using namespace std;

#include "EDG_field.h"

EDG_field::EDG_field() : field(){
}

string EDG_field::name() const {
	return "EDG";
}

string EDG_field::sprite() const {
	return "''''";
}