#pragma once

#include "../field.h"
#include "../includes.h"

/// BCK(background) field
/// 
/// background field - used for filling rest of the map visually
class EDG_field : public field {
public:
	EDG_field();

	string name() const;

	string sprite() const;
private:
};
