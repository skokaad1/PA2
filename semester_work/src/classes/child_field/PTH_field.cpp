using namespace std;
#include "PTH_field.h"

PTH_field::PTH_field() : field() {
	housed = nullptr;
}

PTH_field::~PTH_field() {
}

string PTH_field::name() const {
	return "PTH";
}

string PTH_field::sprite() const {
	if (housed == nullptr) {
		return "    ";
	}
	return housed->sprite();
	//return "errr";
}

 shared_ptr<field> PTH_field::clone() const {
	return make_shared<PTH_field>(PTH_field());
}

 void PTH_field::inhabit(shared_ptr<invader> &invader_ptr) {
	 //typename std::shared_ptr<T>::element_type
	  housed = invader_ptr;
 }