#pragma once

#include "includes.h"
#include "tower.h"
#include "invader.h"
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

	virtual ~field() = default;

	virtual string name() const = 0;

	virtual string sprite() const = 0;

	void inhabit(shared_ptr<tower> tower_ptr);

	void inhabit(shared_ptr<invader> invader_ptr);

	virtual shared_ptr<field> clone() const = 0;


 protected:

};
