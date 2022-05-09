#pragma once

#include "../field.h"
#include "../child_invader/invaders.h"

//=====================================================================================FIELDS
/// PTH(pathway) field
/// 
/// pathway field - used for building pathways on gamemap for invaders to walk through
class PTH_field : public field {
public:
	PTH_field();
	
	~PTH_field();

	string name() const;
private:
	shared_ptr<invader> invader_here;
};