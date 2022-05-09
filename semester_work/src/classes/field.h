#pragma once

#include "includes.h"
using namespace std;

/// parent field
/// 
/// TBD fields, or otherwise board pieces are spots on map for other classes to interact with, this virtual class provides template on how to place them and visualize them
// public: 
//		place(vector<vector<int>>)
//		house()
//		print()
class field {
 public:
	field();

	//virtual ~field() = default;
	
	//bool place(vector<int> &board);

	//void house();

	string name() const;

	virtual string sprite() const = 0;

 protected:

};
