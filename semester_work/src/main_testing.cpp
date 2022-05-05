//#include "classes.h"
#include "graphical_api.cpp"
#include "classes.h"

using namespace std;
int main ( void )
{ 
	cout << "========================" << endl;
	invader b;
	b.damage(2);
	window a;
	a.draw();
	return EXIT_SUCCESS;
}


