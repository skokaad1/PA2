using namespace std;
#include "TWR_field.h"

TWR_field::TWR_field() : field() {
	housed = Pre_made_storage().random_tower();
}

TWR_field::~TWR_field() {
}

string TWR_field::name() const {
	return "START";
}

string TWR_field::sprite() const {
	if (housed != nullptr) { 
		return housed->sprite(); 
	}
	else {
		return "/\\\\/";
	}
}

 shared_ptr<field> TWR_field::clone() const {
	return make_shared<TWR_field>(TWR_field());
}

 void TWR_field::inhabit(shared_ptr<tower> tower_ptr){
	 housed = tower_ptr->clone();
 }