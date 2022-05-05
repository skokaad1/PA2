#ifndef _CLASSES_H
#define _CLASSES_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <thread>
#include <ostream>

class  map {

};

/// parent field
/// 
/// TBD fields, or otherwise board pieces are spots on map for other classes to interact with, this virtual class provides template on how to place them and visualize them
class field {
public:
	void print();
	
	virtual bool place(vector<vector<int>> &board);

	void house();

private:

};

/// parent invader
/// 
/// TBD invaders are player interactible units, this provides template on how to deploy, visualise and work with them, will be split into multiple children classes of different jobs
class invader {
public:
	void damage(int damage);

	void special();

private:
	int health;
	int speed;
};

/// parent tower
/// 
/// TBD towers are ai placed and controlled defenses, this provides template on how they attack, visualize 
class tower {
public:
	void attack(invader& target);
private:
};

#endif