using namespace std;
#include "INT_invader.h"

INT_invader::INT_invader() : invader(5, 3, 4) {

}


string INT_invader::sprite() const {
	return ",,UU";
}

shared_ptr<invader> INT_invader::clone() const {
	return make_shared<INT_invader>(INT_invader());
}