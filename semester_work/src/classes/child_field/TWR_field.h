#pragma once

#include "../field.h"
#include "../includes.h"
#include "../child_tower/towers.h"
#include "../Pre_made.h"

/// TWR(tower) field
/// 
/// tower field - enables tower placement
class TWR_field : public field {
public:
	TWR_field();

	~TWR_field();

	string name() const;

	string sprite() const;

	void inhabit(shared_ptr<tower> tower_ptr);

	virtual shared_ptr<field> clone() const;
private:
	shared_ptr<tower> housed;
};
