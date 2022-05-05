#pragma once

#include "../field.h"
#include "../includes.h"

//=====================================================================================FIELDS
/// PTH(pathway) field
/// 
/// pathway field - used for building pathways on gamemap for invaders to walk through
class PTH_field : public field {
public:
	void render();
private:
};