#pragma once

#include "../field.h"
#include "../includes.h"
#include "PTH_field.h"

/// START(starting field) field
/// 
/// field at the start of map - used for deploying units
class START_field : public PTH_field {
public:
	START_field();

	~START_field();

	string name() const;

	string sprite() const;

	virtual shared_ptr<field> clone() const;
private:
};
