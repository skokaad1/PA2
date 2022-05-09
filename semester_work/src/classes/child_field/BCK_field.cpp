using namespace std;

#include "BCK_field.h"

BCK_field::BCK_field() : field() {
	vector<string> a = { "  /\\" , "  vv" , "  ,," };
	int terrain_type = rand() % 3;
	house = a[terrain_type];
}

string BCK_field::name() const {
	return "BCK";
}

string BCK_field::sprite() const {
	return house;
}