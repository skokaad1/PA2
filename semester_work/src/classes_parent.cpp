using namespace std;
#include "classes_parent.h"

void field::print() {
	cout << "test arena print " << endl; // testing
}
//=============================================
//
//invader======================================
void invader::damage(int damage) {
	cout << "test invader damage " << endl; // testing
}

//=============================================
//
//tower========================================
void tower::attack(invader& target) {
	cout << "test tower attack " << endl; // testing
}
//=============================================

