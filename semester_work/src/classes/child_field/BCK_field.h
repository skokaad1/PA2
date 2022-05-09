#pragma once

#include "../field.h"
#include "../includes.h"
#include <vector>

/// BCK(background) field
/// 
/// background field - used for filling rest of the map visually
class BCK_field : public field {
public:
	BCK_field();

	string name() const;

	string sprite() const;
private:
	string house;
};
