using namespace std;
#include "invader.h"

invader::invader(int inc_health, int inc_speed, int inc_initiative): 
	health(inc_health),
	speed(inc_speed),
	initiative(inc_initiative)
	{
}

invader::invader() {
	health = 1;
	speed = 1;
	initiative = 1;
}


/*void invader::damage(int damage) {
	cout << "sucess" << endl;
}*/

/*string invader::sprite() const {
	return "errr";
}*/

/*shared_ptr<invader> invader::clone() const{
	return make_shared<invader>(invader());
}*/