#pragma once

#include "../field.h"
#include "../includes.h"

/// EDG(edge) field
/// 
/// edge field - used for filling the edges and recognizing them on gameboard
class EDG_field : public field {
public:
	EDG_field();

	~EDG_field();

	string name() const;

	string sprite() const;

	virtual shared_ptr<field> clone() const;
private:
};
