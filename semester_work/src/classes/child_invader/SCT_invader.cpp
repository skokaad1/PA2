using namespace std;
#include "SCT_invader.h"

SCT_invader::SCT_invader() : invader(5, 6, 8) {

}

void SCT_invader::damage(int damage) {
}


string SCT_invader::sprite() const {
	return "<>^^";
}

shared_ptr<invader> SCT_invader::clone() const {
	return make_shared<SCT_invader>(SCT_invader());
}

