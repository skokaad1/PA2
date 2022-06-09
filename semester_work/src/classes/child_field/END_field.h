#pragma once

#include "../field.h"
#include "../includes.h"

/// END(ending field) field
/// 
/// field at the end of map - used for registering win condition
class END_field : public field {
public:
	END_field();

	~END_field();

	string name() const;

	string sprite() const;

	virtual shared_ptr<field> clone() const;
private:
};
