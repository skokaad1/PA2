using namespace std;

#include "BCK_field.h"

BCK_field::BCK_field() : field() {
	vector<string> a = { "HHHH" , "++++" , "$$$$" };
	int terrain_type = rand() % 3;
	house = a[terrain_type];
}

BCK_field::~BCK_field(){

}

string BCK_field::name() const {
	return "BCK";
}

string BCK_field::sprite() const {
	return house;
}

 shared_ptr<field> BCK_field::clone() const {
	return make_shared<BCK_field>(BCK_field());
}