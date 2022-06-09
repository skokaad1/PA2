using namespace std;
#include "ARM_invader.h"

ARM_invader::ARM_invader() : invader(10, 3, 2) {

}

string ARM_invader::sprite() const {
	return "()MM";
}

shared_ptr<invader> ARM_invader::clone() const {
	return make_shared<ARM_invader>(ARM_invader());
}